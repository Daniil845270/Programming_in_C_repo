WARNS := -Wall -Wextra -Wfloat-equal -Wvla -std=c99
DEBUG := $(WARNS) -fsanitize=undefined -fsanitize=address -g3
OPTIM := $(WARNS) -O3
.PHONY: all run rund clean

all: t27 t27_o

t27_o: t27.c t27.h driver.c
	gcc driver.c t27.c $(OPTIM) -o t27_o

t27: t27.c t27.h driver.c
	gcc driver.c t27.c $(DEBUG) -o t27

run: t27
	./t27

runo: t27_o
	./t27_o

clean:
	rm -f t27 t27_o