CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wvla -Wpedantic -std=c99
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testrealloc_s testrealloc_v testrealloc

testrealloc : boolarr.h Realloc/specific.h Realloc/realloc.c testboolarr.c general.h general.c
	$(CC) testboolarr.c Realloc/realloc.c general.c -o testrealloc -I./Realloc $(PRODUCTION) $(LDLIBS)

testrealloc_s : boolarr.h Realloc/specific.h Realloc/realloc.c testboolarr.c general.h general.c
	$(CC) testboolarr.c Realloc/realloc.c general.c -o testrealloc_s -I./Realloc -I$(GENPATH) $(SANITIZE) $(LDLIBS)

testrealloc_v : boolarr.h Realloc/specific.h Realloc/realloc.c testboolarr.c general.h general.c
	$(CC) testboolarr.c Realloc/realloc.c general.c -o testrealloc_v -I./Realloc -I$(GENPATH) $(VALGRIND) $(LDLIBS)


clean:
	rm -f testrealloc_s testrealloc_v testrealloc

run: all
	./testrealloc_s
	valgrind ./testrealloc_v
