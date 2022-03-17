/*
    eratosthenes.h
    IJC-DU1, príklad a), 5.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    Popis:
    deklaracia funkcii eratosthenes a print_primes, ktore su definovane v module eratosthenes.c
*/

#ifndef ERATOSTHENES_H
#define ERATOSTHENES_H

#include "bitset.h"

void eratosthenes(bitset_t * arr);
void print_primes(bitset_t * arr, int amount_of_primes);

#endif
