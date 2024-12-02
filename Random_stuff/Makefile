WARNS := -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -Wpedantic
DEBUG := $(WARNS) -fsanitize=undefined -fsanitize=address -g3
OPTIM := $(WARNS) -O3
.PHONY: all run rund clean

move: move_zeroes.c
	gcc move_zeroes.c $(DEBUG) -o move_zeroes

run: move_zeroes
	./move_zeroes

clean:
	rm -f move_zeroes
