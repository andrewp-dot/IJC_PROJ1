CC = clang
CFLAGS = -O0 -g -std=c11 -pedantic -Wall -Wextra -Werror -lm

make: primes.c 
	${CC} ${CFLAGS} primes.c -o primes
	${CC} ${CFLAGS} -DUSE_INLINE  primes.c -o primes-i

run: make
	./primes
	./primes-i	
32:
	${CC} -m32 primes.c -o primes
	${CC} -m32 -DUSE_INLINE  primes.c -o primes-i
pre:
	${CC} -E primes.c 

clean: 
	rm -rf primes primes-i *dSYM

steg-decode: steg-decode.c 
	${CC} ${CFLAGS} steg-decode.c -o steg-decode
