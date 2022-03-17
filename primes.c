/*
    primes.c
    IJC-DU1, príklad a), 10.3.2111
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    ...popis příkladu - poznámky, omezení, atd
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "eratosthenes.h"
#include "bitset.h"
#include "error.c"


#define N 300000000
//
//CONTROL ARRAY SIZE

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

/*
TO DO

pripis maker do inline funkcii - podmieneny preklad
chybove stavy

assert na max velkost pola
funkciu na dlzku behu programu 
testovat aj pre 32 bit verziu
*/
