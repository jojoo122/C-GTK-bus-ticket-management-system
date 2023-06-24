PRGM = main
CC = gcc
CFLAG = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

${PRGM}: ${PRGM}.c
	clear && ${CC} ${CFLAG} -o ${PRGM} ${PRGM}.c ${LIBS} && ./${PRGM}

run :
	./${PRGM} && clear

rm :
	rm ${PRGM} && clear

test:
	clear && ${CC} ${CFLAG} -o test test.c ${LIBS} && ./test

testrm:
	rm test && clear

push:
	clear && git add . && git commit -m "BTMS" && git pull origin main && git push -u origin main && clear