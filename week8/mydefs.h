// Change this file in any way you like
// Do not alter driver.c / Makefile / md.h
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdbool.h>

#define BRDSZ 6
#define BIG_NUM 1000
#define MAXBRDS 200000 
#define POS long unsigned int

enum ckpt {ckpt_fail, ckpt_pass};
typedef enum ckpt ckpt;

enum myexit {graceful_exit, normal_operation};
typedef enum myexit myexit;

/*
Here define struct state -
it might look something like:

struct board{
   2D array of tiles
   hawk
   parent
}

struct state{
    array of struct board[];
    etc.
}
*/

#include "md.h"

myexit readNcheck_file(const char* fname, char* str);
myexit line_fillup(char* temp_string, char* temp_content_str, int* cnt);
// ckpt hawk_check(char* temp_string);
ckpt only_uprletter(char* temp_string);
// ckpt body_check(char* temp_string);
// ckpt fillupNcheck_hawk(FILE* filepointer, char* temp_string, char* temp_content_str, int* cnt);
// ckpt fillupNcheck_bodyfirst(FILE* filepointer, char* temp_string, char* temp_content_str, int* cnt);
ckpt fillcheck_hawk(FILE* fp, char* temp, char* str, int* cnt);
ckpt fillcheck_fstbody(FILE* fp, char* temp, char* str, int* cnt, POS* rowlen);
ckpt fillcheck_restbody(FILE* fp, char* temp, char* str, int* cnt, POS* rowlen);