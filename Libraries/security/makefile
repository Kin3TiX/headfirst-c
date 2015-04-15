encrypt.o : encrypt.c
	gcc -c encrypt.c -o encrypt.o
checksum.o : checksum.c
	gcc -c checksum.c -o checksum.o
libhfsecurity.a : encrypt.o checksum.o
	ar -rcs libhfsecurity.a encrypt.o checksum.o
testApp : testCode.c libhfsecurity.a
	gcc testCode.c -I . -L . -l hfsecurity -o testApp