# General flags we'll always use
GENFLAGS := -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal 

# -O3 means optimise compiled code for execution speed
OPTIM := $(GENFLAGS) -O3

# Creates a much slower executable but filled with run-time error/bounds checking etc.
# -g flag gives extra debugging information
SANITIZE := $(GENFLAGS) -g3 -fsanitize=address -fsanitize=undefined

# In the labs you might use clang, but make sure to try gcc too
# (sometimes bugs show up 'better' using one compiler than another
CC := gcc
# CC := clang

depth_o: depth.c
	$(CC) depth.c $(OPTIM) -o depth_o

depth: depth.c
	$(CC) depth.c $(SANITIZE) -o depth

all: depth depth_o

run:
	./depth

clean:
	rm -f depth depth_o