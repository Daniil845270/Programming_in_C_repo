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
#define MAXBRDS 500000 //lets be on the safe rather than sorry side of the spectrum

enum checkpoint {checkpoint_fail, checkpoint_pass};
typedef enum checkpoint checkpoint;

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
void line_fillup(char* temp_string, char* temp_content_str, int* fillup_cnt);
checkpoint hawk_check(char* temp_string);
checkpoint only_uprletter(char* temp_string);
checkpoint body_check(char* temp_string);
checkpoint fillupNcheck_hawk(FILE* filepointer, char* temp_string, char* temp_content_str, int* fillup_cnt);
checkpoint fillupNcheck_bodyfirst(FILE* filepointer, char* temp_string, char* temp_content_str, int* fillup_cnt);