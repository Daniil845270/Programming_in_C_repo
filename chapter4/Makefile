FLGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99 -fsanitize=undefined -fsanitize=address -g3

rot18: main.c xp24166_rot18.c rot18.h
	gcc main.c xp24166_rot18.c $(FLGS) -o xp24166_rot18

crosswords: crosswords.c headerfile.h
	gcc crosswords.c $(FLGS) -o crosswords

clean: 
	rm -fr cross
