#
`USE_HAL_I2S_REGISTER_CALLBACKS` wasn't enabled

dsi_host check if works as genereated in audio-loc-proj, as the bsp inits the screen

# setup dsp
https://community.st.com/s/article/configuring-dsp-libraries-on-stm32cubeide

# check 

**Clocks different than generated**
```
RCC_OscInitStruct.PLL.PLLM = 8;
RCC_OscInitStruct.PLL.PLLN = 360;
```

start the pwm
HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);


180 / ((0 + 1) * (58 + 1)) = 3.05084746

## setting up makefile project
- create a project via MX IDE, setup for makefile toolchain, tick box to copy .c and.h files into directory (code generator)
- in vscode install stm32-for-vscode extension
- open stm32-for-vscode panel hit build
- see it failing failing with undefined reference to '__errno'
- open generated file STM32-for-VSCode.config.yaml go to linkerFlags: and add line with - -specs=rdimon.specs
- hit build again and it should compile
- hit Flash STM and it should flash your connected device

- trim down project like mentioned here: https://st.force.com/community/s/article/how-to-add-a-bsp-to-an-stm32cubeide-project

## issues with BSP_AUDIO

wasn't defined in the stm32f4xx_it.c (`AUDIO_I2Sx_DMAx_IRQHandler` alias `DMA1_Stream2_IRQHandler`)
```c
void AUDIO_I2Sx_DMAx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(haudio_in_i2s.hdmarx);
}
```