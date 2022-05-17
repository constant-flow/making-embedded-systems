#include "al_display.h"
#include "stm32469i_discovery_lcd.h"
#include "stm32f4xx.h"
// extern DSI_HandleTypeDef hdsi;

static uint32_t LAYER0_ADDRESS = LCD_FB_START_ADDRESS;

void al_display_init()
{
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(0, LAYER0_ADDRESS);
    BSP_LCD_SelectLayer(0);
}

void al_display_update()
{
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect(0, 0, 800, 112);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(0, 112, 800, 368);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_DisplayStringAtLine(1, (uint8_t *)" Audio Locator");
    // HAL_DSI_Refresh(&hdsi);
}
