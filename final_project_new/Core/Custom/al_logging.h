/**
 ******************************************************************************
 * @file           : al_logging.h
 * @brief          : Handles logging to UART
 * @author         : Constantin Wolf
 ******************************************************************************
 */

#if !defined(HEADER_AL_LOGGING)
#define HEADER_AL_LOGGING

#include "stdio.h"
#include "stdarg.h"

#include "al_led.h"
#include "console.h"

// taken from https://stackoverflow.com/questions/1056411/how-to-pass-variable-number-of-arguments-to-printf-sprintf
void logging_log(const char *format, ...);

#endif // HEADER_AL_LOGGING
