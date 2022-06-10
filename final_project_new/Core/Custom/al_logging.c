#include "al_logging.h"

static char buffer[256];
void logging_log(const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    vsprintf(buffer, format, argptr);
    va_end(argptr);

    ConsoleSendLine(buffer);
}