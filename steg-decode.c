#include <stdlib.h>
#include <stdio.h>

#include "ppm.c"
#include "error.c" 
#include "bitset.h"
#include "eratosthenes.h"

#define START 29
//TO DO 
/*
    dynamicky alokovat struktury
    pridat popis ku kazdemu suboru
    nacitat data do dynamicky alokovanej struktury  
    prerobit do UTF-8 
*/

void filter_message(struct ppm * p)
{
    int data_size = 3*p->xsize*p->ysize;
    bitset_alloc(mask, data_size * TO_BITS);

    eratosthenes(mask);
    bitset_free(mask);
}

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        error_exit("BEZ DO PICE BEZ ARGUMENTU.\n");
    }

    file = ppm_read(argv[1]);
    ppm_free(file);
    decode(ppm);

    return 0;
} 

//     Zpráva je řetězec znaků (char, včetně '\0') uložený po jednotlivých bitech - 
//     (počínaje LSb) na nejnižších bitech (LSb) vybraných bajtů barevných složek
//     v datech obrázku. Dekódování ukončete po dosažení '\0'.

//     Pro DU1 budou vybrané bajty určeny prvočísly (počínaje od 29) -- použijte
//     Eratostenovo síto podobně jako v příkladu "primes.c" a začněte prvočíslem 29.
//     Velikost bitového pole musí odpovídat velikosti obrazových dat RGB.
