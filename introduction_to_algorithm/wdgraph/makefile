LIBS=-lm
CFLAGS=-Wall -std=c99 -g

target=test
objects=main.o wdgraph.o
PWD=$(shell pwd)

test : $(objects)
	cc $(objects) -o $(target)

main.o : wdgraph.h $(PWD)/../ita.h
wdgraph.o : wdgraph.h $(PWD)/../ita.h

.PHONY : clean
clean :
	-rm -f test $(objects)
