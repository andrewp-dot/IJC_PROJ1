/*
    primes.c
    IJC-DU1, príklad a), 10.3.2111
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)

    Popis:
    Hlavna cast programu s funkciou main. Funkcia main vyuziva 
    vsetky moduly potrebne pre inicializaciu bitoveho pola  a pracu s nim (bitset.h),
    modul s eratosthenovym sitom na najdenie a vypis prvocisel (eratosthenes.h)
    a modulom pre vypis hlaseni v pripade chyb (error.c)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "eratosthenes.h"
#include "bitset.h"


#define N 300000000 

int main()
{
    time(NULL);
    setlocale(LC_ALL,"cs_CZ.utf8");
    double start = clock();

    bitset_alloc(bitarr,N); 

    eratosthenes(bitarr);
    print_primes(bitarr,10);
    
    bitset_free(bitarr);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
