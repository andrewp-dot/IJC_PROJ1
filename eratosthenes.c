/*
    eratosthenes.c
    IJC-DU1, príklad a), 5.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    Popis: 
        Funkcia eratoshtenes - eratosthenov algoritmus na vyhladavanie prvočísel,
        funkcia preberá ukazateľ na pole typu bitset_t (unsigned long). Každé prvočíslo
        v tomto poli je po vykonaní algortimu označené 0, násobky prvočísel sú nastavené
        na bit s hodnotou 1.

        Funkcia print_primes - funkcia na vypis prvocisel.
*/

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "bitset.h"

void eratosthenes(bitset_t * arr)
{
    const unsigned long array_size = bitset_size(arr);
    double limit = sqrt(bitset_size(arr));

    for(unsigned long idx = 2; idx <= (unsigned long)limit; idx++)
    {
        if( bitset_getbit(arr,idx) == 0)
        {
            for(unsigned long multiplier = 2; idx*multiplier < array_size; multiplier++)
            {
                bitset_setbit(arr,idx*multiplier,1);
            }
        }
    }
}


//vypsat poslednych 10 prvocisel VZOSTUPNE
void print_primes(bitset_t * arr, int amount_of_primes)
{
    int primes[amount_of_primes];
    int count = 0;
    for(int idx = bitset_size(arr)-1; idx >= 2; idx--)
    {
        if(bitset_getbit(arr,idx) == 0 )
        {
            primes[amount_of_primes-1-count] = idx; //uklada ich reverzne do pola
            if(count == amount_of_primes)break;
            count++;
        }
    }

    for(int primeIdx = 0; primeIdx < amount_of_primes; primeIdx++)
    {
        printf("%d\n", primes[primeIdx]);
    }
}
