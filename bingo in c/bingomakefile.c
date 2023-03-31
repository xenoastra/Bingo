#include <bingo.c>
#include <bingo2.c>
#include <bingolist.c>
#include <bingolist.h>

cc=gcc

  
bingo: bingo.o bingolist.o
    cc bingo.o bingolist.o -o bingo

A2.o: A2.c
      cc -c A2.c -o A2.o
bingolist.o: bingolist.c
      cc -c bingolist.c -o bingolist.o

.PHONY: clean

clean:
	rm -f $(makedir)
    rm *.o bingo
