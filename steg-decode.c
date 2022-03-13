#include <stdlib.h>
#include <stdio.h>

#include "ppm.h"
#include "error.h" 
#include "bitset.h"
#include "eratosthenes.h"

#define START 29
#define LSBFLAG 1
#define MSBINDEX 7 //indexacia cisla 0...7 s

void filter_message(struct ppm *p)
{
    int data_size = 3*p->xsize*p->ysize*sizeof(char);
    char * data = p->data;
    char bit_index = 0;
    char current_bit = 0;
    char current_byte=0;

    //print in unicode I guess
    bitset_alloc(mask, data_size * TO_BITS);
    eratosthenes(mask);

    for(int cIdx = START; cIdx < data_size;cIdx++)
    {
        if(bitset_getbit(mask,cIdx) == 0)
        {
            //printf("%d \n", current_bit);
            current_bit =  data[cIdx] & LSBFLAG<<bit_index; //get current LSB
           // cIdx%7 > 0 ? printf("%d", current_bit > 0 ?  1 : 0) :  printf("\n");

            current_byte |= current_bit; //save it to byte 
            if(bit_index == MSBINDEX) //after completing byte reset everything 
            {
              // printf("\t current byte: %c %d \n", current_byte,current_byte);
                bit_index = 0;
                current_byte = 0;// !!SPRAVY SU ASI V UNICODE !!
                continue;
            }
            bit_index++;
        }
    }

    bitset_free(mask);
}

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        error_exit("BEZ DO PICE BEZ ARGUMENTU.\n");  
    }
  
    struct ppm * file = ppm_read(argv[1]);
    filter_message(file);
    ppm_free(file);
    

    return 0;
} 

//     Zpráva je řetězec znaků (char, včetně '\0') uložený po jednotlivých bitech - 
//     (počínaje LSb) na nejnižších bitech (LSb) vybraných bajtů barevných složek
//     v datech obrázku. Dekódování ukončete po dosažení '\0'.

//     Pro DU1 budou vybrané bajty určeny prvočísly (počínaje od 29) -- použijte
//     Eratostenovo síto podobně jako v příkladu "primes.c" a začněte prvočíslem 29.
//     Velikost bitového pole musí odpovídat velikosti obrazových dat RGB.
