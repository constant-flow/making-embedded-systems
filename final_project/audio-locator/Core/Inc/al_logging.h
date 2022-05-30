#if !defined(HEADER_AL_LOGGING)
#define HEADER_AL_LOGGING

#include "stdio.h"
#include "stdarg.h"

#include "al_led.h"
#include "console.h"

char buffer[256];

// taken from https://stackoverflow.com/questions/1056411/how-to-pass-variable-number-of-arguments-to-printf-sprintf
void logging_log(const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    vsprintf(buffer, format, argptr);
    va_end(argptr);

    ConsoleSendLine(buffer);
}

#endif // HEADER_AL_LOGGING
