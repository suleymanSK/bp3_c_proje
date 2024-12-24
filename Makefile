compile:program
program:library mainFile
	gcc proje1.o main.o -o program
library:
	gcc -c proje1.c -o proje1.o
mainFile:
	gcc -c main.c -o main.o