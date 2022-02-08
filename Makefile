CC=gcc
CFLAGS=#-lpthread

output: main.o
	$(CC) $(CFLAGS) main.o -o output

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o output
