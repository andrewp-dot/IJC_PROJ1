#include<stdlib.h>
#include<stdio.h>
#include <stdarg.h>
#include <string.h>
#include"error.h"

void warning_msg(const char *fmt, ...)
{
     va_list args;

    va_start(args, fmt);

    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr,fmt, args);

    va_end(args);
    exit(1);
}
