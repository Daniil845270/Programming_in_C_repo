#pragma once

/* Put anything you like here, but
   certainly your 'state' structure 
   to hold your board e.g.
*/
#define MAXROWS 20
#define WIDTH 5
#define HEIGHT 6
#define REPLACE_TILE 'R'
#define KEEP_TILE 'K'
#define NO_TILE '.'
#define NO_TILE_FLAG '!'
#define BIG_NUM 10000
#define ALPHABET_LEN 30
#define NULL_OF_STR 26
struct st {
   char board[MAXROWS][WIDTH];
   int rows;
   bool is_board_full;
};
typedef struct st state;


//initialise() functions

//functions related to checking if the input string str could be converted into the state board
bool invalid_init_options(const char* str);
bool invalid_strlen(int* str_len);
bool invalid_strchar(const char* str, int* str_len);
bool match_inputstr_to_ab(const char* str, const char* ab_str, int letter);
void init_uprcase_alphabet(char* str);
//functions converting the str into the whole board
void initialise_board(state* s, const char* str);  
void whole_board_fillup(state* s, const char* str);
void two_d_arr_printer(const state* s); //strictly not part of the algorhythm 
//initialise the board from a file
void check_if_file(const char* str, char* filename_or_string);

//tostring() fucntions

bool alldots_row_check(const state* s, int row);

//matches() functions

void array_fillup_withconstant(char* def_patternrec_str);
void matches_snapshot_update(state* s, state* pattern_rec);
void horisontally_matching_tilesfinder(state* s, state* pattern_rec);
bool horisontal_comparison(state* s, int row, int column, int direction);
void vertically_matching_tilesfinder(state* s, state* pattern_rec);
bool vertical_comparison(state* s, int row, int column, int direction);
void s_update_using_matches_snapshot(state* s, state* pattern_rec, bool* any_mathces);
void s_update_using_matches_snapshot_loop(state* s, state* pattern_rec, int indentaion, bool* any_mathces);

//dropblocks() functions
void tileshifter(state* s, int row, int column);
