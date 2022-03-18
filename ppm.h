/*
    ppm.h
    IJC-DU1, príklad a), 16.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    Popis:
    struct ppm - struktura na spracovanie ppm obrazkov: 
    xsize.ysize - rozmery obrazka, char data [] - data v podobe rgb bajtov
    ppm_read - funkcia, ktora  precita subor v ppm formate a ulozi do alokovanej ppm struktury 
    ppm_free - funkcia na uvolnenie alokovanej struktury
*/

#ifndef PPM_H
#define PPM_H

struct ppm{
    unsigned xsize;
    unsigned ysize;
    char data[];  
};

struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);

#endif
