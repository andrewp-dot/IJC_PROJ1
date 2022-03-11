/*
    primes.c
    IJC-DU1, príklad a), 4.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    
    Popis:
*/


#ifndef BITSET_H
#define BITSET_H

#include "error.h"

#define SPACE_FOR_ARRAY_SIZE 1
#define TO_BITS 8

//bitset array types
typedef unsigned long bitset_t;
typedef unsigned long bitset_index_t;

#define bitset_create(array_name,size) bitset_t array_name[SPACE_FOR_ARRAY_SIZE + (size / (sizeof(bitset_t)*TO_BITS) ) + (size % ( sizeof(bitset_t)*TO_BITS ) != 0 ) ] = { size , 0 }
// definuje a _nuluje_ proměnnou jmeno_pole
//    (POZOR: opravdu musí _INICIALIZOVAT_ pole bez ohledu na
//    to, zda je pole statické nebo automatické/lokální!
//    Vyzkoušejte obě varianty, v programu použijte lokální pole.)
//    Použijte  static_assert  pro kontrolu velikosti pole.
//    Př: static bitset_create(p,100); // p = pole 100 bitů, nulováno
//        bitset_create(q,100000L);    // q = pole 100000 bitů, nulováno
//        bitset_create(q,-100);       // chyba při překladu

#define bitset_alloc(array_name, size) \
bitset_t * array_name = (bitset_t *)calloc( SPACE_FOR_ARRAY_SIZE + (size / ( sizeof(bitset_t)*TO_BITS ) ) + ( size % ( sizeof(bitset_t)*TO_BITS ) != 0), sizeof(bitset_t) ); \
if(array_name == NULL) error_exit("Chyba alokace paměti. \n");\
*array_name = size
//  definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
//        vytvořeným pomocí bitset_create, ale pole bude alokováno dynamicky.
//        Př: bitset_alloc(q,100000L); // q = pole 100000 bitů, nulováno
//        Použijte  assert  pro kontrolu maximální možné velikosti pole.
//        Pokud alokace selže, ukončete program s chybovým hlášením:
//        "bitset_alloc: Chyba alokace paměti"

//zaciatok podmienenho prekladu
#ifdef USE_INLINE

static inline void bitset_free(bitset_t * arr)
{
    free(arr);
}

static inline bitset_t bitset_size(bitset_t * arr)
{
    return arr[0];
}

static inline void bitset_setbit(bitset_t * arr, bitset_index_t index, int exp)
{
     if(index > bitset_size(arr)-1 )  error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu .\n", (unsigned long)index, (unsigned long)(bitset_size(arr)-1));
    if(exp)
    {
        arr[ SPACE_FOR_ARRAY_SIZE + index/( (sizeof(bitset_t)*TO_BITS) ) ] |=  ( (unsigned long)1 << ( index%(sizeof(bitset_t)*TO_BITS) ) );
    }
    else
    {
        arr[ SPACE_FOR_ARRAY_SIZE + index/( (sizeof(bitset_t)*TO_BITS) ) ] &=  ~( (unsigned long)1 << ( index%(sizeof(bitset_t)*TO_BITS) ) );
    }

}

static inline int bitset_getbit(bitset_t *arr, bitset_index_t index)
{
    if( index > bitset_size(arr)-1 )
    {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu .\n", (unsigned long)index, (unsigned long)(bitset_size(arr)-1));
        return 1;
    }
    else
    {
        return ( ( arr[ SPACE_FOR_ARRAY_SIZE + index/( (sizeof(bitset_t)*TO_BITS) ) ] & ((unsigned long)1<<( index%(sizeof(bitset_t)*TO_BITS) ) ) ) > 0 ?  1UL : 0UL );
    }
}

#else

#define bitset_free(array_name) free(array_name); 
// uvolní paměť dynamicky (bitset_alloc) alokovaného pole

#define bitset_size(array_name) array_name[0]
// sizeof(bitset_t) bytes = sizeof(bitset_t)*8 bits;
//    vrátí deklarovanou velikost pole v bitech (uloženou v poli)

#define bitset_setbit(array_name,index,exp)\
if((unsigned long)index > bitset_size(array_name)-1) error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu .\n", (unsigned long)index, (unsigned long)(bitset_size(array_name)));\
if(exp)\
{\
    array_name[ SPACE_FOR_ARRAY_SIZE + ( (index)/( (sizeof(bitset_t)*TO_BITS) ) )] |=  ( (unsigned long)1 << ( index%( (sizeof(bitset_t)*TO_BITS) ) ) );\
}\
else\
{\
     array_name[ SPACE_FOR_ARRAY_SIZE + ( (index)/( (sizeof(bitset_t)*TO_BITS) ) )] &=  ~( (unsigned long)1 << ( index%( (sizeof(bitset_t)*TO_BITS) ) ) );\
}

//    nastaví zadaný bit v poli na hodnotu zadanou výrazem
//    (nulový výraz == bit 0, nenulový výraz == bit 1)
//    Př: bitset_setbit(p,20,1);  

#define bitset_getbit(array_name,index) \
((unsigned long)index > bitset_size(array_name)-1) ?\
error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu .\n", (unsigned long)index, (unsigned long)(bitset_size(array_name)-1)), 0UL\
:\
  ( ( array_name[ SPACE_FOR_ARRAY_SIZE + index/( (sizeof(bitset_t)*TO_BITS) ) ] & ((unsigned long)1<<( index%(sizeof(bitset_t)*TO_BITS) ) ) ) > 0 ?  1UL : 0UL )


//    získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1
//    Př: if(bitset_getbit(p,i)==1) printf("1");
//        if(!bitset_getbit(p,i))   printf("0");

#endif 

#endif
