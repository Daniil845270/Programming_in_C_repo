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
#define MAXBRDS 2000000 
#define POS long unsigned int
#define BIG_NUM_ALT 10000
#define THRD 2
#define FRTH 3
#define FTYFTY 44

enum ckpt {ckpt_fail, ckpt_pass};
typedef enum ckpt ckpt;

enum myexit {graceful_exit, normal_operation};
typedef enum myexit myexit;

enum solv {nosol_exist, solution_found, cont};
typedef enum solv solv;

enum cmpr {differ, same};
typedef enum cmpr cmpr;


// Here define struct state -
// it might look something like:

// struct board{
//    2D array of tiles
//    hawk
//    parent
// }

// struct state{
//     array of struct board[]; (shouldn't be an array of pointers to structures, but an array of structures)
//     number of items in struct board[] (Fs);
//     etc.
// }


struct board{
   char brd[BRDSZ][(BRDSZ+1)];
   char hawk;
   int parent;
   int daughter;
   int rows;
   int clmn;
};
typedef struct board board;

struct state{
   board brdlist[MAXBRDS];
   int pcnt;
   int dcnt;
   bool solved;
};
typedef struct state state;

#include "md.h"

myexit readNcheck_file(const char* fname, char* str);
myexit line_fillup(char* temp_string, char* temp_content_str, int* cnt);
ckpt only_uprletter(const char* temp);
ckpt fillcheck_hawk(FILE* fp, char* temp, char* str, int* cnt);
ckpt fillcheck_fstbody(FILE* fp, char* temp, char* str, int* cnt, POS* rowlen);
ckpt fillcheck_restbody(FILE* fp, char* temp, char* str, int* cnt, POS* rowlen);

bool finclmn_check(state* s, int col);

void copy_strToState(board* board, const char* str);
void structarray_printer(board* b);
ckpt gtkpng(const char* str);

solv find_solution(state* s);
// void create_dauthers(state* s, int col);
void cpyParDtr(state* s);
void shift_tile(state* s, int col);
cmpr find_match(state* s);
cmpr comparator(state* s, int strc);
bool is_solution(state* s, bool edge);
void print_finstructarray(state* s);
int backtrace_solution(state* s, bool verbose);

void on_error(const char* s);
solv find_sol_cont(state* s, int col);


