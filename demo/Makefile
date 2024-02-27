CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -I../

SRCS = ../mm_fifo.c demo.c
OBJS = $(SRCS:.c=.o)
EXEC = demo.out

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
