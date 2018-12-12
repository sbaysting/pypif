CC = gcc

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

default: injector

injector: $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJ) injector
