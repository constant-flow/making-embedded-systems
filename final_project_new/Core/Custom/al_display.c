/**
 ******************************************************************************
 * @file           : al_display.c
 * @brief          : Displays the tracking results for the different modes
 * @author         : Constantin Wolf
 * 
 * MIT License
 *
 * Copyright (c) 2022 Constantin Wolf
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 ******************************************************************************
 */

#include "al_display.h"
#include "stm32469i_discovery_lcd.h"
#include "stm32f4xx.h"
#include "arm_math.h"

// current tracking result
static tracking_dir *tracking = NULL;

// visual parameters

// where to draw the middle of the tracking result
static int tracking_center_x = 0;
static int tracking_center_y = 0;

// indicator
static int x = 80;
static int y = 30;

// indicator framing
static int radius_indicator = 120;
static int radius_cirle = 120;
static int square_height = 60;
static int square_indicator = 60;

// tracking mode
static int last_mode = 0;

// color palette
const static uint32_t AL_COLOR_HEADING_BACKGROUND = 0xff404040;
const static uint32_t AL_COLOR_HEADING_TEXT = 0xffFFB100;
const static uint32_t AL_COLOR_BACKGROUND = 0xff000000;
const static uint32_t AL_COLOR_FRAME = 0xff808080;
const static uint32_t AL_COLOR_INDICATOR = 0xffFFB100;

// styling
static int FONT_H = 24;
static int title_height = 80;
static int screen_width = 0;
static int screen_height = 0;
static int spacing = 20;

// pcm data
static mics_pcm_frame *pcm_frame;

void display_draw_static_parts();
void al_draw_audio(void);

void al_display_init()
{
    BSP_LCD_Init();

    // init vars to ease later drawing
    screen_width = BSP_LCD_GetXSize();
    screen_height = BSP_LCD_GetYSize();
    title_height = spacing * 2 + FONT_H;
    tracking_center_x = screen_width / 2;
    tracking_center_y = (screen_height - title_height) / 2 + title_height;
    radius_cirle = (screen_height - title_height - 2 * spacing) / 2;
    radius_indicator = radius_cirle - spacing;
    square_indicator = square_height - spacing;

    // define layer to draw at
    BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(0);

    BSP_LCD_SetFont(&Font24);

    display_draw_static_parts();
}

// draws title of the app
void display_draw_static_parts()
{
    // HEADING
    BSP_LCD_SetTextColor(AL_COLOR_HEADING_BACKGROUND);
    BSP_LCD_FillRect(0, 0, screen_width, title_height);

    BSP_LCD_SetBackColor(AL_COLOR_HEADING_BACKGROUND);
    BSP_LCD_SetTextColor(AL_COLOR_HEADING_TEXT);
    BSP_LCD_DisplayStringAt(spacing, (title_height - FONT_H) / 2, (uint8_t *)"Audio Locator v2.0", LEFT_MODE);

    // TRACKING AREA
    BSP_LCD_SetTextColor(AL_COLOR_BACKGROUND);
    BSP_LCD_FillRect(0, title_height, screen_width, screen_height);

    if (tracking->mode == MODE_PCB_PLANE)
    {
        // CIRCLE
        BSP_LCD_SetTextColor(AL_COLOR_FRAME);
        BSP_LCD_DrawCircle(tracking_center_x, tracking_center_y, radius_cirle);

        BSP_LCD_SetTextColor(AL_COLOR_HEADING_TEXT);
        BSP_LCD_SetBackColor(AL_COLOR_BACKGROUND);
        BSP_LCD_DisplayStringAt(spacing, (title_height + FONT_H * 1.0f), (uint8_t *)"PCB plane mode", LEFT_MODE);
    }

    else if (tracking->mode == MODE_SCREEN_FRONT)
    {
        // Square
        BSP_LCD_SetTextColor(AL_COLOR_FRAME);
        BSP_LCD_DrawRect(tracking_center_x - radius_cirle, tracking_center_y - square_height / 2, radius_cirle * 2, square_height);

        // draw ticks to get a bit of a 3d effect
        for (int i = 0; i < 180; i += 5)
        {
            float angle = i / 180.0f * PI;
            int x_tick = cos(angle) * radius_cirle + tracking_center_x;
            int y_tick = tracking_center_y + square_height / 2;
            BSP_LCD_DrawLine(x_tick, y_tick, x_tick, y_tick - spacing / 2);
            BSP_LCD_DrawLine(x_tick, y_tick - square_height, x_tick, y_tick - square_height + spacing / 2);
        }

        BSP_LCD_SetTextColor(AL_COLOR_HEADING_TEXT);
        BSP_LCD_SetBackColor(AL_COLOR_BACKGROUND);
        BSP_LCD_DisplayStringAt(spacing, (title_height + FONT_H * 1.0f), (uint8_t *)"Screen front mode", LEFT_MODE);
    }
}

int frame = 0;

void al_display_update()
{
    // drop frames to get load of the screen refresh
    if (frame++ % 10 != 0)
        return;
    if (last_mode != tracking->mode)
    {
        display_draw_static_parts();
    }

    if (tracking->mode == MODE_PCB_PLANE)
    {
        // clear last line with BG color
        BSP_LCD_SetTextColor(AL_COLOR_BACKGROUND);
        int x1 = tracking_center_x;
        int y1 = tracking_center_y;
        int x2 = tracking_center_x + x;
        int y2 = tracking_center_y + y;
        BSP_LCD_DrawLine(x1, y1, x2, y2);
        BSP_LCD_DrawLine(x1+1, y1, x2+1, y2);
        BSP_LCD_DrawLine(x1, y1+1, x2, y2+1);
        BSP_LCD_DrawLine(x1-1, y1, x2-1, y2);
        BSP_LCD_DrawLine(x1, y1-1, x2, y2-1);

        // calculate/draw new indicator direction
        x = tracking->x * radius_indicator;
        y = tracking->y * radius_indicator;
        x2 = tracking_center_x + x;
        y2 = tracking_center_y + y;
        BSP_LCD_SetTextColor(AL_COLOR_INDICATOR);
        // BSP_LCD_DrawLine(tracking_center_x, tracking_center_y, tracking_center_x + x, tracking_center_y + y);
        BSP_LCD_DrawLine(x1, y1, x2, y2);
        BSP_LCD_DrawLine(x1+1, y1, x2+1, y2);
        BSP_LCD_DrawLine(x1, y1+1, x2, y2+1);
        BSP_LCD_DrawLine(x1-1, y1, x2-1, y2);
        BSP_LCD_DrawLine(x1, y1-1, x2, y2-1);
    }
    else if (tracking->mode == MODE_SCREEN_FRONT)
    {
        // clear last line with BG color
        int line_half_height = square_indicator / 2;
        BSP_LCD_SetTextColor(AL_COLOR_BACKGROUND);
        int x1 = tracking_center_x + x;
        int y1 = tracking_center_y - line_half_height;
        int x2 = tracking_center_x + x;
        int y2 = tracking_center_y + line_half_height;
        BSP_LCD_DrawLine(x1, y1, x2, y2);
        BSP_LCD_DrawLine(x1-1, y1+1, x2-1, y2-1);
        BSP_LCD_DrawLine(x1+1, y1+1, x2+1, y2-1);     

        // calculate/draw new indicator direction
        x = tracking->x * radius_indicator;
        y = tracking->y * radius_indicator;
        BSP_LCD_SetTextColor(AL_COLOR_INDICATOR);
        x1 = tracking_center_x + x;
        y1 = tracking_center_y - line_half_height;
        x2 = tracking_center_x + x;
        y2 = tracking_center_y + line_half_height;
        BSP_LCD_DrawLine(x1, y1, x2, y2);
        BSP_LCD_DrawLine(x1-1, y1+1, x2-1, y2-1);
        BSP_LCD_DrawLine(x1+1, y1+1, x2+1, y2-1);   
    }

    last_mode = tracking->mode;

    // al_draw_audio();
}

static int cnt = 0;
// prints pcm data as a wave form
void al_draw_audio(void)
{
    if (cnt % 1000 != 0)
        return; // draw every 1000th time
    uint16_t x = 10;
    uint16_t y = title_height;

    uint16_t audio_area_w = 200;
    uint16_t audio_area_h = 50;

    BSP_LCD_SetTextColor(0xff202020);

    BSP_LCD_FillRect(x, y, audio_area_w, audio_area_h * 2);

    uint16_t gap = audio_area_w / pcm_frame->count;

    y = title_height + audio_area_h;
    BSP_LCD_SetTextColor(AL_COLOR_INDICATOR);

    for (int i = 0; i < pcm_frame->count; i++)
    {
        // uint16_t y_end = y + (uint16_t)((pcm_frame->pdm_samples[i] / (float)UINT16_MAX) * audio_area_h); // raw PDM data
        uint16_t y_end = y + (uint16_t)((pcm_frame->samples[i] / (float)UINT16_MAX) * audio_area_h); // PCM data
        if (y_end < 0)
            y_end = 0;

        if (y_end > 480)
            y_end = 480;

        BSP_LCD_DrawLine(x, y, x, y_end);
        x += gap;
    }
}

void display_set_tracking(tracking_dir *dir)
{
    tracking = dir;
}

void display_set_audio(mics_pcm_frame *new_pcm_frame)
{
    pcm_frame = new_pcm_frame;
}
