FLGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99 -fsanitize=undefined -fsanitize=address -g3

rot18: main.c rot18.c rot18.h
	gcc main.c rot18.c $(FLGS) -o rot18
	
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

clean: 
	rm -fr rot18 fibonacciwordex1 fibonacciwordex2 palindromes int_to_string delete roman_numberals
