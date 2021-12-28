CC=gcc

output: main.o
	$(CC) main.o -o output

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o output
