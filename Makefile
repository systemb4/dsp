CC=gcc
CFLAGS=#-lpthread
INPUT=input/list.nagl

output: main.o
	$(CC) $(CFLAGS) main.o -o output

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o output
