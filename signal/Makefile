CC  := gcc
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%,$(SRC)) # convert all *.c to * , e.g. something.c to something

CFLAGS := -ggdb -lpthread

all: $(OBJ)

.PHONY: clean
clean:
	-rm $(OBJ)


%: %.c
	 -$(CC) $< -o $@ $(CFLAGS)
