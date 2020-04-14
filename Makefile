list-test : List.o list-test.o
	gcc -o list-test List.o list-test.o

List.o : List.c List.h
	gcc -c List.c

list-test.o : list-test.c
	gcc -c list-test.c

clean :
	rm list-test List.o list-test.o
