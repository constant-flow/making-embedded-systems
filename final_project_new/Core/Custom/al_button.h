/**
 ******************************************************************************
 * @file           : al_button.h
 * @brief          : Handles user button via Interrupt, calls registered 
 *                   callback
 * @author         : Constantin Wolf
 ******************************************************************************
 */

#if !defined(HEADER_AL_BUTTON)
#define HEADER_AL_BUTTON

// initialize and register function to be called
void button_init(void (*callback)(void));
void EXTI0_IRQHandler();

#endif // HEADER_AL_BUTTON
