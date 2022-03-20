/*
    ppm.h
    IJC-DU1, príklad a), 18.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    Popis:
    filter_message - funkcia na vyfiltrovanie spravy zo zadaneho ppm suboru
    funkcia main - hlavna cast programu, ziskanie a spracovanie ppm suboru 
    a dekodovanie tajnej spravy v subore
    
*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "ppm.h"
#include "error.h" 
#include "bitset.h"
#include "eratosthenes.h"

#define START 29
#define LSB 1
#define MSBINDEX 7//indexacia cisla 0...7 s

void filter_message(struct ppm *image)
{
    bitset_t data_size = 3*image->xsize*image->ysize*sizeof(char);
    char * data = image->data;

    char bit_index = 0;
    char current_byte = 0;
    
    bitset_alloc(mask, data_size);
    eratosthenes(mask);


    for(int charIdx = START; charIdx < (int)data_size; charIdx++)
    {
        
        if(bitset_getbit(mask,charIdx) == 0)
        {
            if(data[charIdx] & LSB) current_byte |= (1<<bit_index); 
             //save it to byte to it's position
       
            if(bit_index == MSBINDEX) //after completing byte reset everything 
            {   
                if(current_byte == 0) break;
                printf("%c", current_byte);
                bit_index = 0;
                current_byte = 0;
                charIdx++;
                continue;
            }
            bit_index++;
        }
    }
    printf("\n");
    bitset_free(mask);
}

int main(int argc, char ** argv)
{
    setlocale(LC_CTYPE, "cs_CZ.utf8");
    if(argc != 2)
    {
        error_exit("Malý počet argumentov.\n");  
    }   
    struct ppm * file = ppm_read(argv[1]);
    filter_message(file);
    ppm_free(file);

    return 0;
} 
