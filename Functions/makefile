comparators.o  : comparators.h comparators.c
	gcc -c comparators.c
scores.o : scores.h comparators.h scores.c
	gcc -c scores.c
SCORES : scores.o comparators.o
	gcc scores.o comparators.o -o SCORES
