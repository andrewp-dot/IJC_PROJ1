#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"

#ifdef USE_INLINE

extern inline void bitset_free(bitset_t * arr);
extern inline bitset_t bitset_size(bitset_t * arr);
extern inline void bitset_setbit(bitset_t * arr, bitset_index_t index, int exp);
extern inline int bitset_getbit(bitset_t *arr, bitset_index_t index);

#endif
