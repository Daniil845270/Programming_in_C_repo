WARNS := -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -Wpedantic
DEBUG := -fsanitize=undefined -fsanitize=address -g3
OPTIM := -O3

maze_o: maze721.c headerfile.h
	gcc maze721.c $(WARNS) $(OPTIM) -o maze721_o

maze: maze721.c headerfile.h
	gcc maze721.c $(WARNS) $(DEBUG) -o maze721

run: maze721
	./maze721

clear:
	rm -f maze721 maze721_o