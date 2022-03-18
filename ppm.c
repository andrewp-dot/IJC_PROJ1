/*
    ppm.h
    IJC-DU1, príklad a), 16.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    Popis:
    implementacie funkcii ppm_read a ppm_free z modulu ppm.h
*/

#include <stdlib.h>
#include <stdio.h>

#include "ppm.h"
#include "error.h"

struct ppm * ppm_read(const char * filename)
{
    //otvaranie suboru
    FILE *ppm_file= fopen(filename,"r");
    if(ppm_file == NULL)
    {
        warning_msg("Nepodarilo sa otvorit subor. \n");
        fclose(ppm_file);
        return NULL;
    }

    // scanovanie a urcenie velkosti dat
    int x, y;
    if(fscanf(ppm_file, "P6 %d %d 255", &x, &y)==EOF) error_exit("Subor je v zlom formáte.\n");
    unsigned long size = 3*x*y;

    //overenie velkosti obrazka pre zadany limit 
    if( x > 8000 || y > 8000)
    {
        warning_msg("Obrazok je prilis velky. \n");
        fclose(ppm_file);
        return NULL;
    }

    //dynamicka alokacia struktury
    struct ppm * image = (struct ppm *)malloc(size*sizeof(char) + sizeof(struct ppm));
    if(image == NULL)
    {
        warning_msg("Nepodarilo sa alokovat strukturu.\n");
        fclose(ppm_file);
        return NULL;
    }

    image->xsize = x;
    image->ysize = y;
  
    fread(image->data, sizeof(char), size, ppm_file );
    fclose(ppm_file);

    return image;
}

void ppm_free(struct  ppm *p)
{
    free(p);
}
