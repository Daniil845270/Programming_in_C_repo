CC=clang
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal -O1 
LDLIBS= -lm

crossword : crossword_a2.c cwddriver.c crossword.h
	$(CC) crossword_a2.c cwddriver.c -o crossword_a2 $(CFLAGS) $(LDLIBS)

clean :
	rm -f crossword_a2