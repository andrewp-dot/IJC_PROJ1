/*
    bitset.h
    IJC-DU1, príklad a), 11.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    Popis:
    Deklaracia funkcii pre modul error.c
*/

#ifndef ERROR_H
#define ERROR_H

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);


#endif
