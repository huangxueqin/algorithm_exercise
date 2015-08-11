test : main.o graph.o graphutils.o queue.o stack.o
	cc -g -o test main.o graph.o graphutils.o queue.o stack.o

graph.o : _c_graph.c _c_graph.h
	cc -g -c _c_graph.c -o graph.o

graphutils.o : _c_graph_utils.c _c_graph_utils.h
	cc -g -c _c_graph_utils.c -o graphutils.o

queue.o : queue.c queue.h
	cc -g -c queue.c -o queue.o

stack.o : stack.c stack.h
	cc -g -c stack.c -o stack.o

main.o : graphUtilsTest.c
	cc -g -c graphUtilsTest.c -o main.o

.PHONY : clean

clean:
	rm -f test main.o graph.o graphutils.o queue.o stack.o
