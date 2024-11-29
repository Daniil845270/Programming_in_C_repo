#include "crushit.h"
#include "mydefs.h"


bool initialise(state* s, const char* str)
{
    if (s == NULL || str == NULL){
        return false;
    }

    char filename_or_string[BIG_NUM] = {'0'};
    check_if_file(str, filename_or_string);

    if (invalid_init_options(filename_or_string) == true){
        return false;
    }

    initialise_board(s, filename_or_string); 
    return true;
}


void check_if_file(const char* str, char* filename_or_string)
{
    for (long unsigned int letter = 0; letter < strlen(str); letter++){
        filename_or_string[letter] = str[letter];
    }
     
    FILE* filepointer = fopen(filename_or_string, "r"); 
    if (filepointer != NULL){
        char temp_string[BIG_NUM] = {'0'};
        char temp_filecontent_string[BIG_NUM] = {'0'};
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
    int total_board_rows = strlen(str) / WIDTH;
    s->rows = total_board_rows;

    whole_board_fillup(s, str);

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

bool invalid_init_options(const char* str)
{
    int str_len = strlen(str);

    if (invalid_strlen(&str_len) == true || invalid_strchar(str, &str_len) == true){ 
        return true;
    }

    return false;
}

bool invalid_strlen(int* str_len)
{
    if (*str_len % 5 != 0 || *str_len > (MAXROWS * WIDTH) || *str_len == 0){
        return true;
    }
    return false;
}

bool invalid_strchar(const char* str, int* str_len)
{
    int str_cnt = 0;
    char ab_str[ALPHABET_LEN] = {0};
    init_uprcase_alphabet(ab_str);
    while (str_cnt != *str_len && (match_inputstr_to_ab(str, ab_str, str_cnt) == true || str[str_cnt] == NO_TILE)){
        str_cnt++;        
    }
    if (str_cnt != *str_len){
        return true;
    }
    return false;
}

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

void init_uprcase_alphabet(char* ab_str)
{
    for (int letter = 0; letter <= ('Z' - 'A'); letter++){
        ab_str[letter] = 'A' + letter;
    }
    ab_str[('Z' + 1)] = '\0'; //if you initialise ab_str to have the length of 27, then this line is not needed strictly speaning
}
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

bool tostring(const state* s, char* str) 
{
    if (s == NULL || str == NULL){
        return false;
    }

    bool is_alldots_row = false; int str_cnt = 0;
    for (int row = 0; row < s->rows; row++){
        for (int column = 0; column < WIDTH; column++){
            if (column == 0){
                is_alldots_row = alldots_row_check(s, row);
            }
            if (is_alldots_row == false){
                str[str_cnt] = s-> board[row][column];
                str_cnt++;
            }
        }
    }
    str[str_cnt] = '\0';
    return true;
}

bool alldots_row_check(const state* s, int row)
{
    for (int column = 0; column < WIDTH; column++){
        if (s->board[row][column] != NO_TILE){
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
    if (s == NULL){
        return false;
    }

    state matches_snapshot; matches_snapshot.rows = 6;

    char def_matches_snapshot_str[31];
    array_fillup_withconstant(def_matches_snapshot_str);
    whole_board_fillup(&matches_snapshot, def_matches_snapshot_str);

    matches_snapshot_update(s, &matches_snapshot);

    bool any_mathces = false; 
    s_update_using_matches_snapshot(s, &matches_snapshot, &any_mathces);

    if (any_mathces == true){
        return true;
    }
    else{
        return false;
    }
}

void s_update_using_matches_snapshot(state* s, state* matches_snapshot, bool* any_mathces)
{
    
    if (s->is_board_full == true){
        s_update_using_matches_snapshot_loop(s, matches_snapshot, (s->rows - HEIGHT), any_mathces);
    }
    else{
        s_update_using_matches_snapshot_loop(s, matches_snapshot, 0, any_mathces);
    }
}

void s_update_using_matches_snapshot_loop(state* s, state* matches_snapshot, int indentaion, bool* any_mathces)
{ 
    for (int row = 0; row < HEIGHT; row++){
        for (int column = 0; column < WIDTH; column++){
            if (matches_snapshot->board[row][column] == REPLACE_TILE){
                s->board[(row + indentaion)][column] = NO_TILE; 
                *any_mathces = true;
            }
        }
    }
}

void matches_snapshot_update(state* s, state* matches_snapshot)
{
    horisontally_matching_tilesfinder(s, matches_snapshot);
    vertically_matching_tilesfinder(s, matches_snapshot);
}

void horisontally_matching_tilesfinder(state* s, state* matches_snapshot)
{
    for (int row = 0; row < matches_snapshot->rows && row < s->rows; row++){
        for (int column = 1; column < (WIDTH - 1); column++){
            if (horisontal_comparison(s, row, column, 1) == true && horisontal_comparison(s, row, column, -1) == true){
                matches_snapshot->board[row][column - 1] = REPLACE_TILE;
                matches_snapshot->board[row][column] = REPLACE_TILE;
                matches_snapshot->board[row][column + 1] = REPLACE_TILE;
            }
        }
    }
}

void vertically_matching_tilesfinder(state* s, state* matches_snapshot)
{
    for (int row = 1; row < matches_snapshot->rows - 1 && row < s->rows - 1; row++){
        for (int column = 0; column < WIDTH; column++){
            if (vertical_comparison(s, row, column, 1) == true && vertical_comparison(s, row, column, -1) == true){
                matches_snapshot->board[row - 1][column] = REPLACE_TILE;
                matches_snapshot->board[row][column] = REPLACE_TILE;
                matches_snapshot->board[row + 1][column] = REPLACE_TILE;
            }
        }
    }
}

bool horisontal_comparison(state* s, int row, int column, int direction)
{
    int adj_row;
    if (s->is_board_full == true){
        adj_row = s->rows - HEIGHT + row;
        if ((s->board[(adj_row)][column] != NO_TILE)){
            if (s->board[(adj_row)][column] == s->board[(adj_row)][column + direction]){   
                return true;
            }
        }
        return false;
    }
    else{
        if ((s->board[row][column] != NO_TILE)){
            if (s->board[row][column] == s->board[row][column + direction]){
                return true;
            }
        }
        return false;
    }
    return false; 
}

bool vertical_comparison(state* s, int row, int column, int direction)
{
    if (s->is_board_full == true){
        int adj_row = s->rows - HEIGHT + row;
        if (s->board[adj_row][column] != NO_TILE){
            if (s->board[adj_row][column] == s->board[(adj_row + direction)][column]){
                return true; 
            }
        }
        return false;
    }
    else{
        if (s->board[row][column] != NO_TILE){
            if (s->board[row][column] == s->board[row + direction][column]){
                return true;
            }
        }
        return false;
    }
    return false; 
}

void array_fillup_withconstant(char* def_matches_snapshot_str)
{
    for (int letter = 0; letter < WIDTH * HEIGHT; letter++){
        def_matches_snapshot_str[letter] = KEEP_TILE;
    }
    def_matches_snapshot_str[(WIDTH * HEIGHT)] = '\0';
}

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

bool dropblocks(state* s)
{
    if (s == NULL){
        return false;
    }

    for (int row = s->rows - 1; row > 0; row--){
        for (int column = 0; column < WIDTH; column++){
            tileshifter(s, row, column);
        }
    }
    return true;
}

void tileshifter(state* s, int row, int column)
{
    while (s->board[row][column] == NO_TILE){
        for (int shifter_row = row; shifter_row > 0; shifter_row--){
            s->board[shifter_row][column] = s->board[shifter_row - 1][column];
        }
        s->board[0][column] = NO_TILE_FLAG;
    }

    for (int row = 0; row < s->rows; row++){
        for (int column = 0; column < WIDTH; column++){
            if (s->board[row][column] == NO_TILE_FLAG){
                s->board[row][column] = NO_TILE;
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


    // assert(initialise(&s, "mytest_19row1_file.txt") == true);

    // assert(tostring(&s, str) == true);
    // assert(matches(&s)==true);
    // assert(strcmp(str, "BCBCCCBBBCACAABBBACBAABBBCABCBCBBCBBBCCACBACCCABAACBCBAACCBCABBCAAAACABCBCCCCAAACBBBCBCBABBBCCB") == 0);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(matches(&s)==true);
    // assert(strcmp(str, "B...CCC.CCABBBBBCBABABACBCAABBCABCBBBBCACBBCCCBCCACAAAAABBBCACCBABBCCACCBCCCCBCCBCBABBBCCB") == 0);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(matches(&s)==true);
    // assert(strcmp(str, "B...CC...CA...BB...BAC.CBCBBBBCCBABBBACACAABCCABCACBBCAABBCCABCCABAAAACBBBCCCCBCBBCABBBCCB") == 0);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(matches(&s)==true);
    // assert(strcmp(str, "B...CC...CA...BB...BA...BC..CBCC.BBBB.AACC.CCCBBBACABCAAAACCABACABBBCCCBBBCBBBABBBCCB") == 0);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(matches(&s)==true);
    // assert(strcmp(str, "....C....C....BB...BC...BA...BB...BA...AC...CC..CAB..BAC..ACCC.CACBBBCACBCCCBAABBACCB") == 0);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "....C....C....B....B....B....BB...BC...AA...CB...AA..CAC..BCC..AABC.CCACBCCCBAABBACCB") == 0);
    // assert(matches(&s)==false);


    // assert(initialise(&s, "mytest_20row1_file.txt") == true);


    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "BABABACBBBCABABACABACCCCCACACCCAABBCBBAACCBCAAACABAAABCABCBACBBAAACABAABABBBCBBACAABBCCCCBACCBCBCCBB") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "....BB...BA...BCAB.AACBACCABBCACAABCCCBACCACACAACBABBBCACBAAAACCACAAAAABCBBABBBABCAABCBABBACBBCBAABB") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "....BB...BA...BC...AAAB.CCCB.CAAB.BCCA.ACCCAACCABBAAAACABBBAACBCACACCAAAABBABCAABCACBCBAABACBBCBAAAB") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "....B....BB...BA...AC...CA...CCAB.BACB.ACAB.ACCAABCCCBCACAAAAAABAABBCACCBCBAACBABBCABCCACBABAACBCBBB") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "....BB...BA...BC...AA...CCA..CACB.BCAB.ACCB.ACCAABACCBCAAAAAABABACCBCAAABCBBBCBACCCABABACBBCAAC") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "....B....BB...BA...AC...CA...CCA..BACB.ACAB.ACCBABCCABCACCAAAAABAABACACCBCBAABBABBCABABACBBCAAC") == 0);
    // assert(matches(&s)==false);

    // assert(initialise(&s, "mytest_10row1_fileZ.txt") == true);
    // assert(tostring(&s, str) == true);
    // assert(strcmp(str,    "ZCCZXZXCXCZZCXCXXXCZCXXCCXXZCZCZZXXZZXZCXCZZZZZCZZ") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str,    "ZC...ZXC.XZZC.CXXCZCCXXXZXXXXCCZZCZZZZCXXCXCCZZCXZ") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str,    "....XZ...CZC..CZXC.ZXZC.CCXC.ZCZZ.XXCXZCZZCXZ") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);

    // assert(tostring(&s, str) == true);
    // assert(strcmp(str,    "....XZ...CZC..CZX..ZXZ..CCX..ZCZZ.XXCXZCZZCXZ") == 0);
    // assert(matches(&s)==false);

    // assert(initialise(&s, "mytest_3row1_fileZ.txt") == true);
    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "ACZACAZZCAZZZCC") == 0);
    // assert(matches(&s)==true);
    // assert(dropblocks(&s)==true);
    // assert(tostring(&s, str) == true);
    // assert(strcmp(str, "...ACAC.CAAZ.CC") == 0);
    // assert(matches(&s)==false);
    
}
