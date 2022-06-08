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