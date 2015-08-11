main : main.o priority_queue.o
	gcc -o main main.o priority_queue.o

priority_queue.o : priority_queue.c priority_queue.h
	gcc -c priority_queue.c

main.o : main.c priority_queue.h
	gcc -c main.c


