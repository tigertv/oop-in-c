.PHONY: clean all
MAKEFLAGS += --no-builtin-rules

CC = gcc 
OPT = -std=c11 -Wall
SRC = $(wildcard *.c)
BIN := $(SRC:.c=)

all: $(BIN)

%: %.o
	$(CC) $(OPT) $< -o $@
%.o: %.c
	$(CC) $(OPT) -c $< -o $@ 
clean: 
	rm -rf $(BIN)
