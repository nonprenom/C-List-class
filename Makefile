list-test : List.o list-test.o xmalloc.o
	gcc -o list-test List.o list-test.o xmalloc.o

List.o : List.c List.h
	gcc -c -g List.c

list-test.o : list-test.c
	gcc -c -g list-test.c

xmalloc.o : xmalloc.c
	gcc -c -g xmalloc.c

clean :
	rm list-test List.o list-test.o xmalloc.o
