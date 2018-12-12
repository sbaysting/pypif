CC = gcc

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LDFLAGS = -DPSAPI_VERSION=1 -lPsapi

default: injector

injector: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) injector
