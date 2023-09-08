#include "log.h"

#include "stdio.h"
#include "stdarg.h"

void log_info( const char *format, ...) {
    va_list args;
    va_start( args, format );
    vprintf(format, args );
    va_end(args);
    putchar('\n');
}

void log_warn( const char *format, ...) {
    va_list args;
    va_start( args, format );
    vprintf(format, args );
    va_end(args);
    putchar('\n');
}

void log_debug( const char *format, ...) {
    va_list args;
    va_start( args, format );
    vprintf(format, args );
    va_end(args);
    putchar('\n');
}
