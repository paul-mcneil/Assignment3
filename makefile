OBJS = filefunctions.o tokenizer.o main.o sorted-list.o index.o hashmap.o mergesort.o
CC = gcc
CFLAGS = -g -Wall

indexer: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o indexer
