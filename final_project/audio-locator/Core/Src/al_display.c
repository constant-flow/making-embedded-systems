#include "al_display.h"
#include "stm32469i_discovery_lcd.h"
#include "stm32f4xx.h"
// extern DSI_HandleTypeDef hdsi;

static uint32_t LAYER0_ADDRESS = LCD_FB_START_ADDRESS;

static tracking_dir *last_tracking = NULL;

static int tracking_center_x = 0;
static int tracking_center_y = 0;
static int x = 80;
static int y = 30;
static int radius_indicator = 120;
static int radius_cirle = 120;

const static uint32_t AL_COLOR_HEADING_BACKGROUND = 0xff404040;
const static uint32_t AL_COLOR_HEADING_TEXT = 0xffFFB100;
const static uint32_t AL_COLOR_BACKGROUND = 0xff000000;
const static uint32_t AL_COLOR_CIRCLE = 0xff808080;
const static uint32_t AL_COLOR_INDICATOR = 0xffFFB100;

static int title_height = 80;
static int FONT_H = 24;
static int screen_width = 0;
static int screen_height = 0;
static int spacing = 20;

static mics_pcm_frame *pcm_frame;

// private functions
void display_draw_title();

// function implementations
void al_display_init()
{
    BSP_LCD_Init();

    screen_width = BSP_LCD_GetXSize();
    screen_height = BSP_LCD_GetYSize();

    title_height = spacing * 2 + FONT_H;

    tracking_center_x = screen_width / 2;
    tracking_center_y = (screen_height - title_height) / 2 + title_height;
    radius_cirle = (screen_height - title_height - 2 * spacing) / 2;
    radius_indicator = radius_cirle - spacing;

    BSP_LCD_LayerDefaultInit(0, LAYER0_ADDRESS);
    BSP_LCD_SelectLayer(0);

    BSP_LCD_SetFont(&Font24);

    display_draw_title();
}

// draws title of the app
void display_draw_title()
{
    // HEADING
    BSP_LCD_SetTextColor(AL_COLOR_HEADING_BACKGROUND);
    BSP_LCD_FillRect(0, 0, screen_width, title_height);

    BSP_LCD_SetBackColor(AL_COLOR_HEADING_BACKGROUND);
    BSP_LCD_SetTextColor(AL_COLOR_HEADING_TEXT);
    BSP_LCD_DisplayStringAt(spacing, (title_height - FONT_H) / 2, (uint8_t *)"Audio Locator v.01", LEFT_MODE);

    // TRACKING AREA
    BSP_LCD_SetTextColor(AL_COLOR_BACKGROUND);
    BSP_LCD_FillRect(0, title_height, screen_width, screen_height);

    // CIRCLE
    BSP_LCD_SetTextColor(AL_COLOR_CIRCLE);
    BSP_LCD_DrawCircle(tracking_center_x, tracking_center_y, radius_cirle);
}

void al_display_update()
{
    // clear last line with BG color
    BSP_LCD_SetTextColor(AL_COLOR_BACKGROUND);
    BSP_LCD_DrawLine(tracking_center_x, tracking_center_y, tracking_center_x + x, tracking_center_y + y);

    // calculate/draw new indicator direction
    x = last_tracking->x * radius_indicator;
    y = last_tracking->y * radius_indicator;
    BSP_LCD_SetTextColor(AL_COLOR_INDICATOR);
    BSP_LCD_DrawLine(tracking_center_x, tracking_center_y, tracking_center_x + x, tracking_center_y + y);
    // HAL_DSI_Refresh(&hdsi);

    al_draw_audio();
}

volatile a = 0;
int cnt = 0;
void al_draw_audio(void)
{
    uint16_t x = 10;
    uint16_t y = title_height;

    uint16_t audio_area_w = 400;
    uint16_t audio_area_h = 100;

    if (cnt++ % 2)
        BSP_LCD_SetTextColor(0xff202020);
    else
        BSP_LCD_SetTextColor(0xff000000);
    BSP_LCD_FillRect(x, y, audio_area_w, audio_area_h * 2);

    uint16_t gap = audio_area_w / pcm_frame->count;

    y = title_height + audio_area_h;
    BSP_LCD_SetTextColor(AL_COLOR_INDICATOR);

    for (int i = 0; i < pcm_frame->count; i++)
    {
        if (pcm_frame->pdm_samples[i] != 0)
        {
            a = pcm_frame->pdm_samples[i]; // checks if PDM is anything but 0, so far not :(
        }
    }

    for (int i = 0; i < pcm_frame->count; i++)
    {
        // uint16_t y_end = y + (uint16_t)((pcm_frame->pdm_samples[i] / (float)UINT16_MAX) * audio_area_h); // raw PDM data
        uint16_t y_end = y + (uint16_t)((pcm_frame->samples[i] / (float)UINT16_MAX) * audio_area_h); // PCM data
        if (y_end < 0)
            y_end = 0;

        if (y_end > 480)
            y_end = 480;

        BSP_LCD_DrawLine(x, y, x, y_end);
        BSP_LCD_DrawLine(x + 1, y, x + 1, y_end);
        BSP_LCD_DrawLine(x - 1, y, x - 1, y_end);
        x += gap;
    }
}

void display_set_tracking(const tracking_dir *dir)
{
    last_tracking = dir;
}

void display_set_audio(mics_pcm_frame *new_pcm_frame)
{
    pcm_frame = new_pcm_frame;
}
