test : wgraph.o test.o
	cc -g wgraph.o test.o -lm -o test

wgraph.o : wgraph.c wgraph.h
	cc -g -c wgraph.c -o wgraph.o

test.o : test.c
	cc -g -c test.c -o test.o

.PHONY : clean
clean :
	rm -f wgraph.o test.o test
