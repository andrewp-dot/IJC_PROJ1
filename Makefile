CC = clang
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra -Werror -lm

make: primes.c bitset.c eratosthenes.c error.c
	${CC} ${CFLAGS}  -o primes  primes.c bitset.c eratosthenes.c error.c
	${CC} ${CFLAGS} -o primes-i -DUSE_INLINE  primes.c bitset.c eratosthenes.c error.c

run: make
	./primes
	./primes-i	
32:
	${CC} ${CFLAGS} -m32 -o primes  primes.c bitset.c eratosthenes.c error.c
	${CC} ${CFLAGS} -m32 -o primes-i -DUSE_INLINE  primes.c bitset.c eratosthenes.c error.c
pre:
	${CC} -E primes.c 

clean: 
	rm -rf primes primes-i steg-decode *.o *dSYM *.zip

steg-decode: steg-decode.c ppm.c eratosthenes.c error.c
	${CC} ${CFLAGS} -o steg-decode steg-decode.c ppm.c eratosthenes.c error.c
	
zip: 
	zip -r du1.zip *.h *.c Makefile du1-obrazek.ppm 
