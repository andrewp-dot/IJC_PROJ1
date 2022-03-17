#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "ppm.h"
#include "error.h" 
#include "bitset.h"
#include "eratosthenes.h"

#define START 29
#define LSB 1
#define MSBINDEX 7//indexacia cisla 0...7 s

void  filter_message(struct ppm *p, wchar_t * msg)
{
    int data_size = 3*p->xsize*p->ysize*sizeof(char);
    char * data = p->data;

    char bit_index = 0;
    char current_bit = 0;
    char current_byte=0;

    //char msg[101];
    int msgI = 0;

    //print in unicode I guess
    bitset_alloc(mask, data_size * TO_BITS);
    eratosthenes(mask);

    for(int cIdx = START; cIdx < data_size;cIdx++)
    {
        
        if(bitset_getbit(mask,cIdx) == 0)
        {
            current_bit =  data[cIdx] & LSB;//get current LSB
            //bit_index%7 ? printf("%d", current_bit > 0 ?  1 : 0) :  printf("\n");

            current_byte |= current_bit<<bit_index; //save it to byte to it's position
            if(bit_index == MSBINDEX) //after completing byte reset everything 
            {
                if((int)current_byte >= 32 && (int)current_byte<=126) printf("%c", current_byte);
                // *msg= current_byte;
                // *(msg+msgI+ 1) = '\0';
                bit_index = 0;
                current_byte = 0;// !!SPRAVY SU ASI V UNICODE !!
                msgI++;
                continue;
            }
            bit_index++;
        }
    }

    bitset_free(mask);
}

int main(int argc, char ** argv)
{
    setlocale(LC_CTYPE, "cs_CZ.utf8");
    if(argc != 2)
    {
        error_exit("BEZ DO PICE BEZ ARGUMENTU.\n");  
    }   

  
    struct ppm * file = ppm_read(argv[1]);
    
    wchar_t message;
    filter_message(file, &message);

    /*const wchar_t * message = filter_message(file);
    int i = 0;
    while (*(message + i) != '\0')
    {
        fprintf(stdout, "%c", *(message+i));
        i++;
    }
    */
    ppm_free(file);

    return 0;
} 

//     Zpráva je řetězec znaků (char, včetně '\0') uložený po jednotlivých bitech - 
//     (počínaje LSb) na nejnižších bitech (LSb) vybraných bajtů barevných složek
//     v datech obrázku. Dekódování ukončete po dosažení '\0'.

//     Pro DU1 budou vybrané bajty určeny prvočísly (počínaje od 29) -- použijte
//     Eratostenovo síto podobně jako v příkladu "primes.c" a začněte prvočíslem 29.
//     Velikost bitového pole musí odpovídat velikosti obrazových dat RGB.
