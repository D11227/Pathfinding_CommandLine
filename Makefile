CC = gcc

INCLUDE = -I ./include

CFLAGSO = -w ${INCLUDE}

LIBS =

CFLAGSB = ${LIBS}

build:
	${CC} ./src/*.c ${CFLAGSO} ${CFLAGSB} -o main -lm

clean:
	rm main
