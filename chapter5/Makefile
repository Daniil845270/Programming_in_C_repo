WARNS := -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -Wpedantic
DEBUG := -fsanitize=undefined -fsanitize=address -g3
OPTIM := -O3

gcc_anagrams: anagrams.c headerfile.h
	gcc anagrams.c $(WARNS) $(OPTIM) -o gcc_anagrams

gcc_anagrams_d: anagrams.c headerfile.h
	gcc anagrams.c $(WARNS) $(DEBUG) -o gcc_anagrams_d

clang_anagrams: anagrams.c headerfile.h
	gcc anagrams.c $(WARNS) $(OPTIM) -o clang_anagrams

clang_anagrams_d: anagrams.c headerfile.h
	gcc anagrams.c $(WARNS) $(DEBUG) -o clang_anagrams_d

run: gcc_anagrams_d
	./gcc_anagrams_d

clear:
	rm -f gcc_anagrams gcc_anagrams_d clang_anagrams clang_anagrams_d