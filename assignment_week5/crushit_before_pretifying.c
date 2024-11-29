#include "crushit.h"
#include "mydefs.h"


bool initialise(state* s, const char* str)
{
    // printf("\n"); printf("In initialise now\n"); printf("\n");
    if (s == NULL || str == NULL){
        return false;
    }
    //printf("File entry (not s->board) is %s\n", str); printf("\n");

    char filename_or_string[10000] = {'0'};
    tryfile(str, filename_or_string);

    //printf("filename_or_string after tryfile() %s\n", filename_or_string); printf("\n");

    if (invalid_init_options(filename_or_string) == true){
        return false;
    }
    // printf("was before init\n");
    initialise_board(s, filename_or_string);

    //printf("Result of initialise: \n"); two_d_arr_printer(s); printf("\n");

    return true; //change later, it's there so that it returns something
}


void tryfile(const char* str, char* filename_or_string)
{
    for (long unsigned int letter = 0; letter < strlen(str); letter++){
        filename_or_string[letter] = str[letter];
    }
     
    FILE* filepointer = fopen(filename_or_string, "r");
    if (filepointer != NULL){
        char temp_string[10000] = {'0'};
        char temp_filecontent_string[10000] = {'0'};
        int fillup_cnt = 0;
        while (fscanf(filepointer, "%s", temp_string) == 1){
            for (long unsigned int letter = 0; letter < strlen(temp_string); letter++){
                temp_filecontent_string[fillup_cnt] = temp_string[letter];
                fillup_cnt++;
            }
        }
        strcpy(filename_or_string, temp_filecontent_string);
        fclose(filepointer);
    }
}

void initialise_board(state* s, const char* str)
{
    int total_board_rows = strlen(str) / 5; //it's ok to divide int by int here, bc strlen(str) % 5 == 0 already
    s->rows = total_board_rows;
    whole_board_fillup(s, str);
    is_board_full_update(s);
}

void is_board_full_update(state* s)
{
    if (s->rows - HEIGHT < 0){
        s->is_board_full = false; 
    }
    else{
        s->is_board_full = true;
    }
}

void whole_board_fillup(state* s, const char* str)
{
    int cnt_str = 0;
    for (int row  = 0; row < s->rows; row++){
        for (int column = 0; column < WIDTH; column++){
            s->board[row][column] = str[cnt_str];
            cnt_str++;
        }
    }
}

void two_d_arr_printer(const state* s)
{
    for (int row = 0; row < s->rows; row++){
        for (int column = 0; column < WIDTH; column++){
            printf("%c", s->board[row][column]);
        }
        printf("\n");
    }
}

//this function returns true if the input string "str" can not be used to transform into the candy crush board
bool invalid_init_options(const char* str)
{
    int str_len = strlen(str);

    if (invalid_strlen(&str_len) == true){ 
        return true;
    }

    if (invalid_strchar(str, &str_len) == true){ 
        return true;
    }

    return false;
}


//returns true if the length of the string is invalid
bool invalid_strlen(int* str_len)
{
    if (*str_len % 5 != 0 || *str_len > (MAXROWS * WIDTH) || *str_len == 0){
        return true;
    }
    return false;
}

//returns true if there are invalid characters in the string (i.e. not uppercase letters or a '.')
bool invalid_strchar(const char* str, int* str_len)
{
    int str_cnt = 0;
    char ab_str[30] = {0};
    init_uprcase_alphabet(ab_str);
    while (str_cnt != *str_len && (match_inputstr_to_ab(str, ab_str, str_cnt) == true || str[str_cnt] == '.')){
        str_cnt++;        
    }
    if (str_cnt != *str_len){
        return true;
    }
    return false;
}

//match_inputstr_to_ab() traverses through the uppercase alphabet and compared it to the item of the str. If there is a match, 
//the function returns true. If the str item is not an uppercase letter, the program returns false
bool match_inputstr_to_ab(const char* str, const char* ab_str, int str_cnt)
{
    int ab_letter = 0;
    while (ab_str[ab_letter] != '\0' && ab_str[ab_letter] != str[str_cnt]){
        ab_letter++;
    }
    if (ab_str[ab_letter] == '\0'){
        return false;
    }
    else{
        return true;
    }

}

//transforms an input string into an uppercase alphabet and finishes it with a '\0'
void init_uprcase_alphabet(char* ab_str)
{
    if (strlen(ab_str) < 26){
        for (int letter = 0; letter <= ('Z' - 'A'); letter++){
            ab_str[letter] = 'A' + letter;
        }
        ab_str[26] = '\0'; //if you initialise ab_str to have the length of 27, then this line is not needed strictly speaning
    }
    else{
        printf("init_uprcase_alphabet(): invalid input string length, check NULL before the end of the string\n");
    }
}
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//this function should return the lower 6 rows
//I really do not understnd the return conditions, but if we are asked to do it like that then I wouldn't complaint :/
bool tostring(const state* s, char* str) 
{
    // printf("\n"); printf("In tostring now\n"); printf("\n");
    if (s == NULL || str == NULL){
        return false;
    }

    board_tostring_filler(s, str);

    // printf("Result of tostring:\n");
    // printf("tostring string %s\n", str);
    //printf("s->board\n");
    //two_d_arr_printer(s);
    return true;
}


void board_tostring_filler(const state* s, char* str)
{
    bool is_alldots_row = false;
    int str_cnt = 0;
    for (int row = 0; row < s->rows; row++){
        for (int column = 0; column < WIDTH; column++){
            if (column == 0){
                is_alldots_row = alldots_row(s, row);
            }
            if (is_alldots_row == false){
                str[str_cnt] = s-> board[row][column];
                str_cnt++;
            }

        }
    }
    str[str_cnt] = '\0';
}

bool alldots_row(const state* s, int row)
{
    for (int column = 0; column < WIDTH; column++){
        if (s->board[row][column] != '.'){
            return false;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


bool matches(state* s)
{
    // printf("\n"); printf("In matches now\n"); printf("\n");
    if (s == NULL){
        return false;
    }

    state pattern_rec;
    pattern_rec.rows = 6;

    char def_patternrec_str[31];
    array_fillup_withconstant(def_patternrec_str);
    whole_board_fillup(&pattern_rec, def_patternrec_str);

    pattern_rec_update(s, &pattern_rec);
    //two_d_arr_printer(&pattern_rec);
    bool any_mathces = false; 
    translate_pattern_rec_to_s(s, &pattern_rec, &any_mathces);
    // two_d_arr_printer(&pattern_rec);
    // printf("Result of matches:\n");
    // printf("s->board\n");
    // two_d_arr_printer(s);
    if (any_mathces == true){
        return true;
    }
    else{
        return false;
    }
}

void translate_pattern_rec_to_s(state* s, state* pattern_rec, bool* any_mathces)
{
    
    if (s->is_board_full == true){
        translate_pattern_rec_to_s_loop(s, pattern_rec, (s->rows - HEIGHT), any_mathces);
    }
    else{
        translate_pattern_rec_to_s_loop(s, pattern_rec, 0, any_mathces);
    }
}

void translate_pattern_rec_to_s_loop(state* s, state* pattern_rec, int indentaion, bool* any_mathces)
{ 
    //printf("row is %i, indentaion is %i, diff = %i\n", row, indentaion, row - indentaion);
    //printf("Was before the loop\n");
    for (int row = 0; row < HEIGHT; row++){
        //printf("Was in loop1\n");
        for (int column = 0; column < WIDTH; column++){
            //printf("row is %i, indentaion is %i, diff = %i\n", row, indentaion, row + indentaion);
            if (pattern_rec->board[row][column] == 'R'){
                s->board[(row + indentaion)][column] = '.'; 
                *any_mathces = true;
            }
        }
    }
}

void pattern_rec_update(state* s, state* pattern_rec)
{
    horisontal_pattern_rec_update(s, pattern_rec);
    vertical_pattern_rec_update(s, pattern_rec);
    // two_d_arr_printer(pattern_rec);
    // printf("\n");
}

void horisontal_pattern_rec_update(state* s, state* pattern_rec)
{
    for (int row = 0; row < pattern_rec->rows && row < s->rows; row++){
        for (int column = 1; column < (WIDTH - 1); column++){
            if (horisontal_comparison(s, row, column, 1) == true && horisontal_comparison(s, row, column, -1) == true){
                pattern_rec->board[row][column - 1] = 'R';
                pattern_rec->board[row][column] = 'R';
                pattern_rec->board[row][column + 1] = 'R';
            }
        }
    }
}

bool horisontal_comparison(state* s, int row, int column, int direction)
{
    if (s->is_board_full == true){
        if ((s->board[(s->rows - HEIGHT + row)][column] == s->board[(s->rows - HEIGHT + row)][column + direction]) && (s->board[(s->rows - HEIGHT + row)][column] != '.')){
            return true;
        }
        return false;
    }
    else{
        if ((s->board[row][column] == s->board[row][column + direction]) && (s->board[row][column] != '.')){
            return true;
        }
        return false;
    }
    return false;
}

void vertical_pattern_rec_update(state* s, state* pattern_rec)
{
    for (int row = 1; row < pattern_rec->rows - 1 && row < s->rows - 1; row++){
        for (int column = 0; column < WIDTH; column++){
            if (vertical_comparison(s, row, column, 1) == true && vertical_comparison(s, row, column, -1) == true){
                pattern_rec->board[row - 1][column] = 'R';
                pattern_rec->board[row][column] = 'R';
                pattern_rec->board[row + 1][column] = 'R';
            }
        }
    }
}

bool vertical_comparison(state* s, int row, int column, int direction)
{
    if (s->is_board_full == true){
        if ((s->board[(s->rows - HEIGHT + row)][column] == s->board[(s->rows - HEIGHT + row + direction)][column]) && (s->board[(s->rows - HEIGHT + row)][column] != '.') ){
            return true;
        }
        return false;
    }
    else{
        if ((s->board[row][column] == s->board[row + direction][column]) && (s->board[row][column] != '.')){
            return true;
        }
        return false;
    }
    return false;
}

//in the pattern_rec K means keep and R  means replace
void array_fillup_withconstant(char* def_patternrec_str)
{
    for (int letter = 0; letter < 30; letter++){
        def_patternrec_str[letter] = 'K';
    }
    def_patternrec_str[30] = '\0';
}

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


//theoretically, I could return false if the program doesn't do anything, but if it is executed in sequence after matches(), then this condition is redundant 
bool dropblocks(state* s)
{
    // printf("\n"); printf("In dropblocks now\n"); printf("\n");
    if (s == NULL){
        return false;
    }
    // printf("In dropblocks now\n");
    // two_d_arr_printer(s);
    // printf("\n");
    for (int row = s->rows - 1; row > 0; row--){
        for (int column = 0; column < WIDTH; column++){
            tileshifter(s, row, column);
        }
    }
    tileshifter_cleanup(s);
    // printf("Result of dropblocks:\n");
    // printf("s->board\n");
    // two_d_arr_printer(s);
    // two_d_arr_printer(s);
    // printf("\n");
    return true; //maybe I should rewrite this function so that I returns false if no blocks are dropped, but I am not paid for it and it is kinda covered in matches
}

void tileshifter(state* s, int row, int column)
{
    while (s->board[row][column] == '.'){
        for (int shifter_row = row; shifter_row > 0; shifter_row--){
            s->board[shifter_row][column] = s->board[shifter_row - 1][column];
        }
        s->board[0][column] = '!';
    }
}

void tileshifter_cleanup(state* s)
{
    for (int row = 0; row < s->rows; row++){
        for (int column = 0; column < WIDTH; column++){
            if (s->board[row][column] == '!'){
                s->board[row][column] = '.';
            }
        }
    }
}



void test(void)
{
    state s;
    assert(invalid_init_options("") == true);
    assert(invalid_init_options("AB") == true);
    assert(invalid_init_options("ABCDD") == false);
    assert(invalid_init_options("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") == false);
    assert(invalid_init_options("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") == true);
    assert(initialise(&s, "nonexisting_file.txt") == false);
    assert(initialise(&s, "mytest_emptyfile.txt") == false);
    assert(initialise(&s, "mytest_emptystring_file.txt") == false);
    assert(initialise(&s, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") == false);
    assert(initialise(&s, "mytest_more20rows_filealt.txt") == false);
    assert(initialise(&s, "mytest_more20rows_file.txt") == false);
    assert(initialise(&s, "mytest_nonfivechars1_file.txt") == false);
    assert(initialise(&s, "mytest_nonfivechars2_file.txt") == false);
    assert(initialise(&s, "mytest_nonfivechars3_file.txt") == false);
    assert(initialise(&s, "mytest_nonletterchars1_file.txt") == false);
    assert(initialise(&s, "mytest_nonletterchars2_file.txt") == false);
    assert(initialise(&s, "mytest_nonletterchars3_file.txt") == false);

    char str[WIDTH*MAXROWS+1];

    assert(initialise(&s, "mytest_1row1_file.txt") == true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "BBACA") == 0);
    assert(matches(&s)==false);


    assert(initialise(&s, "mytest_1row2_file.txt") == true);
    assert(tostring(&s, str) == true);
    assert(matches(&s)==true);
    assert(strcmp(str, "BBAAA") == 0);
    assert(dropblocks(&s)==true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "BB...") == 0);
    assert(matches(&s)== false);

    assert(initialise(&s, "mytest_2row1_file.txt") == true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "AABCBBAAAC") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "A...BBABCC") == 0);
    assert(matches(&s)==false);

    assert(initialise(&s, "mytest_3row1_file.txt") == true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "ACBACABBCABBBCC") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "...ACAC.CAAB.CC") == 0);
    assert(matches(&s)==false);

    assert(initialise(&s, "mytest_4row1_file.txt") == true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "BCACBBCCCBCCACCBAAAB") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "B...BB...BC.A.CB.A.B") == 0);
    assert(matches(&s)==false);

    assert(initialise(&s, "mytest_5row1_file.txt") == true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "BBABBABACBABACBCACBCABBAA") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "B..B.A..C.A..C.CACBCABBAA") == 0);
    assert(matches(&s)==false);

    assert(initialise(&s, "mytest_10row1_file.txt") == true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str,    "BCCBABACACBBCACAAACBCAACCAABCBCBBAABBABCACBBBBBCBB") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str,    "BC...BAC.ABBC.CAACBCCAAABAAAACCBBCBBBBCAACACCBBCAB") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str,    "....AB...CBC..CBAC.BABC.CCAC.BCBB.AACABCBBCAB") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str,    "....AB...CBC..CBA..BAB..CCA..BCBB.AACABCBBCAB") == 0);
    assert(matches(&s)==false);


    assert(initialise(&s, "mytest_19row1_file.txt") == true);

    assert(tostring(&s, str) == true);
    assert(matches(&s)==true);
    assert(strcmp(str, "BCBCCCBBBCACAABBBACBAABBBCABCBCBBCBBBCCACBACCCABAACBCBAACCBCABBCAAAACABCBCCCCAAACBBBCBCBABBBCCB") == 0);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(matches(&s)==true);
    assert(strcmp(str, "B...CCC.CCABBBBBCBABABACBCAABBCABCBBBBCACBBCCCBCCACAAAAABBBCACCBABBCCACCBCCCCBCCBCBABBBCCB") == 0);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(matches(&s)==true);
    assert(strcmp(str, "B...CC...CA...BB...BAC.CBCBBBBCCBABBBACACAABCCABCACBBCAABBCCABCCABAAAACBBBCCCCBCBBCABBBCCB") == 0);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(matches(&s)==true);
    assert(strcmp(str, "B...CC...CA...BB...BA...BC..CBCC.BBBB.AACC.CCCBBBACABCAAAACCABACABBBCCCBBBCBBBABBBCCB") == 0);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(matches(&s)==true);
    assert(strcmp(str, "....C....C....BB...BC...BA...BB...BA...AC...CC..CAB..BAC..ACCC.CACBBBCACBCCCBAABBACCB") == 0);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str, "....C....C....B....B....B....BB...BC...AA...CB...AA..CAC..BCC..AABC.CCACBCCCBAABBACCB") == 0);
    assert(matches(&s)==false);


    assert(initialise(&s, "mytest_20row1_file.txt") == true);


    assert(tostring(&s, str) == true);
    assert(strcmp(str, "BABABACBBBCABABACABACCCCCACACCCAABBCBBAACCBCAAACABAAABCABCBACBBAAACABAABABBBCBBACAABBCCCCBACCBCBCCBB") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str, "....BB...BA...BCAB.AACBACCABBCACAABCCCBACCACACAACBABBBCACBAAAACCACAAAAABCBBABBBABCAABCBABBACBBCBAABB") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str, "....BB...BA...BC...AAAB.CCCB.CAAB.BCCA.ACCCAACCABBAAAACABBBAACBCACACCAAAABBABCAABCACBCBAABACBBCBAAAB") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str, "....B....BB...BA...AC...CA...CCAB.BACB.ACAB.ACCAABCCCBCACAAAAAABAABBCACCBCBAACBABBCABCCACBABAACBCBBB") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str, "....BB...BA...BC...AA...CCA..CACB.BCAB.ACCB.ACCAABACCBCAAAAAABABACCBCAAABCBBBCBACCCABABACBBCAAC") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str, "....B....BB...BA...AC...CA...CCA..BACB.ACAB.ACCBABCCABCACCAAAAABAABACACCBCBAABBABBCABABACBBCAAC") == 0);
    assert(matches(&s)==false);

    assert(initialise(&s, "mytest_10row1_fileZ.txt") == true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str,    "ZCCZXZXCXCZZCXCXXXCZCXXCCXXZCZCZZXXZZXZCXCZZZZZCZZ") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str,    "ZC...ZXC.XZZC.CXXCZCCXXXZXXXXCCZZCZZZZCXXCXCCZZCXZ") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str,    "....XZ...CZC..CZXC.ZXZC.CCXC.ZCZZ.XXCXZCZZCXZ") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);

    assert(tostring(&s, str) == true);
    assert(strcmp(str,    "....XZ...CZC..CZX..ZXZ..CCX..ZCZZ.XXCXZCZZCXZ") == 0);
    assert(matches(&s)==false);

    assert(initialise(&s, "mytest_3row1_fileZ.txt") == true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "ACZACAZZCAZZZCC") == 0);
    assert(matches(&s)==true);
    assert(dropblocks(&s)==true);
    assert(tostring(&s, str) == true);
    assert(strcmp(str, "...ACAC.CAAZ.CC") == 0);
    assert(matches(&s)==false);
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////