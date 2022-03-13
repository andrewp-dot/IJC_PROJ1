CC = clang
CFLAGS = -O0 -g -std=c11 -pedantic -Wall -Wextra -Werror 
MATHFLAG = -lm

make: primes.c 
	${CC} ${CFLAGS} primes.c -o primes ${MATHFLAG}
	${CC} ${CFLAGS} -DUSE_INLINE  primes.c -o primes-i  ${MATHFLAG}

run: make
	./primes
	./primes-i	
32:
	${CC} -m32 primes.c -o primes
	${CC} -m32 -DUSE_INLINE  primes.c -o primes-i
pre:
	${CC} -E primes.c 

clean: 
	rm -rf primes primes-i steg-decode *.o *dSYM

steg-decode: steg-decode.c ppm.c eratosthenes.c error.c
	${CC} ${CFLAGS} steg-decode.c ppm.c eratosthenes.c error.c -c
	${CC} ${CFLAGS} steg-decode.o ppm.o eratosthenes.o error.o -o steg-decode
