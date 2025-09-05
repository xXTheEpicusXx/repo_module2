#compiler
CC = gcc
CFALGS = -Wall -Werror -Wextra -Iunity -Isrc

#dirs and files
SRC = src
TEST = tests/tests.c
UNITY = unity/*.c
PROG =  src/double_linked_list.c src/contacts.c

all:
	gcc $(CFALGS) $(PROG) main.c -o bin/contacts

test:
	gcc $(CFALGS) $(PROG) $(TEST) $(UNITY) -o bin/test

clear:
	rm -rf bin/*

