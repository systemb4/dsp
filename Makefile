CC=gcc
CFLAGS=#-lpthread
BINS := $(SRCS:%.c=%)
DEPS = src/nachtigal.h

output: main.o
	$(CC) $(CFLAGS) main.o -o output

main.o: main.c
	$(CC) -c main.c

clean:
	rm -rvf *.o ${BINS}
