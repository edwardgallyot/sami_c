
#include <stdio.h>
#include <stdarg.h>

#include "log.h"

// Logger function
void log_error(const char *file, int line, const char *func, const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[%s %s] ERROR at %s:%d in %s(): ", __DATE__, __TIME__, file, line, func);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

