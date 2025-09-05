#compiler
CC = gcc
CFALGS = -Wall -Wextra -Iunity -Isrc

#dirs and files
SRC = src
TEST = tests/tests.c
UNITY = unity/*.c
PROG =  src/queue.c

all:
	gcc $(CFALGS) $(PROG) main.c -o bin/queue

test:
	gcc $(CFALGS) $(PROG) $(TEST) $(UNITY) -o bin/test

clear:
	rm -rf bin/*
