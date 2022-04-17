# nachtigal

CC=gcc
CFLAGS=#-lpthread
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)
DEPS = src/nachtigal.h

all: ${BINS}

%: %.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $<

clean:
	rm -rvf *.o ${BINS}
