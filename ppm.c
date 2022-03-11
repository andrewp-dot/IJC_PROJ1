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
    fscanf(ppm_file, "P6 %d %d 255", &x, &y);
    unsigned long size = 3*x*y;

    //overenie velkosti obrazka pre zadany limit 
    if( x > 8000 || y > 8000)
    {
        warning_msg("Obrazok je prilis velky. \n");
        fclose(ppm_file);
        return NULL;
    }

    //dynamicka alokacia struktury
    struct ppm * pp = (struct ppm *)malloc(size*sizeof(char) + sizeof(struct ppm));
    if(pp == NULL)
    {
        warning_msg("Nepodarilo sa alokovat strukturu.\n");
        fclose(ppm_file);
        return NULL;
    }

    pp->xsize = x;
    pp->ysize = y;
  
    fread(pp->data, sizeof(char), size, ppm_file );

    printf("x: %d y: %d \n", pp->xsize, pp->ysize);

    fclose(ppm_file);

    return pp;
}

void ppm_free(struct  ppm *p)
{
    free(p);
}

//  * Napište modul "ppm.c" s rozhraním "ppm.h",
//    ve kterém definujete typ:

//      struct ppm {
//         unsigned xsize;
//         unsigned ysize;
//         char data[];    // RGB bajty, celkem 3*xsize*ysize
//      };

//    a funkci:

//      struct ppm * ppm_read(const char * filename);
//         načte obsah PPM souboru do touto funkcí dynamicky
//         alokované struktury. Při chybě formátu použije funkci warning_msg
//         a vrátí NULL.  Pozor na "memory leaks".

//     Popis formátu PPM najdete na Internetu, implementujte pouze
//     binární variantu P6 s barvami 0..255 a bez komentářů:
//       "P6" <ws>+
//       <xsizetxt> <ws>+ <ysizetxt> <ws>+
//       "255" <ws>
//       <binární data, 3*xsize*ysize bajtů RGB>
//       <EOF>

//   * Napište testovací program "steg-decode.c", kde ve funkci main načtete ze
//     souboru zadaného jako jediný argument programu obrázek ve formátu PPM
//     a v něm najdete uloženou "tajnou" zprávu. Zprávu vytisknete na stdout.

//     Program použije error_exit v případě chyby čtení souboru (chybný formát),
//     a v případě, že zpráva není korektně ukončena '\0'. Předpokládejte
//     možnost uložení textu zprávy ve formátu UTF-8.

//     Použijte program "make" pro překlad/sestavení programu.
//     Testovací příkaz:  ./steg-decode du1-obrazek.ppm
