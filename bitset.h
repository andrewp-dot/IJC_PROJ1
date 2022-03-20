/*
    bitset.h
    IJC-DU1, príklad a), 4.3.2022
    Autor: Adrián Ponechal, FIT
    Přeloženo: Apple clang version 13.0.0 (clang-1300.0.27.3)
    
    Popis:
    bitset_create - macro funkcia  definuje a nuluje premennu array_name/arr
    bitset_alloc - macro ako bitset_create, ale pole tvori alokaciou pamate
    bitset_free - macro/ inline funkcia, ktora uvloni alokovane pole
    bitset_size - macro/ inline funkcia, ktora zobrazi velkost bitoveho pola vytvoreneho pomocou bitset_create/bitset_alloc
    bitset_setbit - macro/ inline funkcia, ktora nastavi zvoleny bit v bitovom poli na zvolenu hodnotu
    bitset_getbit - macro/ inline funkcia, ktora zobrazi hodnotu bitu na zvolenej pozicii 
*/


#ifndef BITSET_H
#define BITSET_H

#include <assert.h>
#include "error.h"


#define SPACE_FOR_ARRAY_SIZE 1
#define TO_BITS 8
#define MAX_ARRAY_SIZE 300000000 

//bitset array types
typedef unsigned long bitset_t;
typedef unsigned long bitset_index_t;

#define bitset_create(array_name,size) bitset_t array_name[SPACE_FOR_ARRAY_SIZE + (size / (sizeof(bitset_t)*TO_BITS) ) + (size % ( sizeof(bitset_t)*TO_BITS ) != 0 ) ] = { size , 0 };\
static_assert(size <= MAX_ARRAY_SIZE, "Zadana velkost pola je prilis velka.");

#define bitset_alloc(array_name, size)\
bitset_t * array_name = (bitset_t *)calloc( SPACE_FOR_ARRAY_SIZE + (size / ( sizeof(bitset_t)*TO_BITS ) ) + ( size % ( sizeof(bitset_t)*TO_BITS ) != 0), sizeof(bitset_t) );\
if(array_name == NULL) error_exit("bitset_alloc: Chyba alokace paměti. \n");\
*array_name = size;\
assert(size <= MAX_ARRAY_SIZE);

//zaciatok podmienenho prekladu
#ifdef USE_INLINE

inline void bitset_free(bitset_t * arr) 
{
    free( arr );
}

inline bitset_t bitset_size(bitset_t * arr)
{
    return arr[0];
}

inline void bitset_setbit(bitset_t * arr, bitset_index_t index, int exp)
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

inline int bitset_getbit(bitset_t *arr, bitset_index_t index)
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


#define bitset_size(array_name) array_name[0]


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

#define bitset_getbit(array_name,index) \
((unsigned long)index > bitset_size(array_name)-1) ?\
error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu .\n", (unsigned long)index, (unsigned long)(bitset_size(array_name)-1)), 0UL\
:\
  ( ( array_name[ SPACE_FOR_ARRAY_SIZE + index/( (sizeof(bitset_t)*TO_BITS) ) ] & ((unsigned long)1<<( index%(sizeof(bitset_t)*TO_BITS) ) ) ) > 0 ?  1UL : 0UL )

#endif 

#endif
