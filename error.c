/*
    bitset.h
    IJC-DU1, príklad a), 11.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    Popis:
    warning_msg - variadicka funkcia, ktora len vypise chybove hlasenie v pripade vyskytu chyby
    error_exit - variadicka funkcia, ktora v pripade vyskytu chyby vypise hlasenie a ukonci program 
*/

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
