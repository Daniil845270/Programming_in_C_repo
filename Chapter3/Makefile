FLGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99 -fsanitize=undefined -fsanitize=address -g3

rot18: main.c xp24166_rot18.c rot18.h
	gcc main.c xp24166_rot18.c $(FLGS) -o xp24166_rot18
	
fib: rot18.h fibonacciwordex1.c
	gcc fibonacciwordex1.c $(FLGS) -o fibonacciwordex1
	
fib2: rot18.h fibonacciwordex2.c
	gcc fibonacciwordex2.c $(FLGS) -o fibonacciwordex2

palindromes: rot18.h palindromes.c
	gcc palindromes.c $(FLGS) -o palindromes

integer: rot18.h int_to_string.c
	gcc int_to_string.c $(FLGS) -o int_to_string -lm

delete: rot18.h delete.c
	gcc delete.c $(FLGS) -o delete -lm

roman: rot18.h roman_numberals.c
	gcc roman_numberals.c $(FLGS) -o roman_numberals -lm

sound: rot18.h soundex_coding.c
	gcc soundex_coding.c $(FLGS) -o soundex_coding -lm

sound1: rot18.h soundex_codingalt1.c
	gcc soundex_codingalt1.c $(FLGS) -o soundex_codingalt1 -lm

test: rot18.h function_tester.c
	gcc function_tester.c $(FLGS) -o test -lm


clean: 
	rm -fr soundex_coding xp24166_rot18 fibonacciwordex1 fibonacciwordex2 palindromes int_to_string delete roman_numberals soundex_codingalt1 test

