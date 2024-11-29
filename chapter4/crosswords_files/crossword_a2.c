#include "crossword.h"

void square_two_d_arr_printer(int border, crossword* cw);
void oned_to_twod_array(char* ip, crossword* cw);
void meet_conditions_for_aX_and_down(const crossword* c, char across[], char down[]);
void fill_up_for_aX_and_down(char array[], int* cnt_ax_d, int* cnt_num);
void merge_aX_and_down_into_str(char* str, char across[], char down[]);
bool facross(const crossword* c, int line, int letter);
bool fdown(const crossword* c, int line, int letter);
bool iswhite(const crossword* c, int line, int letter);
bool isblack(const crossword* c, int line, int letter);
void check_orange(const crossword* c, int line, int letter, int* cnt_orange);
void check_white(const crossword* c, int line, int letter, int* cnt_white);
bool check_updown(const crossword* c, int line, int letter);
bool check_leftright(const crossword* c, int line, int letter);

// Get percentage of empty squares that are shared between two clues
int getchecked(crossword c)
{
    int cnt_orange = 0;
    int cnt_white = 0;
    for (int line = 0; line < c.sz; line++){
        for (int letter = 0; letter < c.sz; letter++){
            check_white(&c, line, letter, &cnt_white);
            check_orange(&c, line, letter, &cnt_orange);
        }
    }

    if (cnt_white == 0){
        printf("No white squares\n");
        return -1;
    }
    printf("was here\n");
    square_two_d_arr_printer(c.sz, &c);
    float fcnt_orange = cnt_orange, fcnt_white = cnt_white, percentage;
    percentage = (fcnt_orange * 100) / fcnt_white;
    int int_percentage = round(percentage);
    return int_percentage;
}

void check_orange(const crossword* c, int line, int letter, int* cnt_orange)
{
    if (check_updown(c, line, letter) && check_leftright(c, line, letter)){
        (*cnt_orange)++;
    }
}

bool check_updown(const crossword* c, int line, int letter)
{
    if (iswhite(c, line, letter) && (((line > 0) && iswhite(c, (line - 1), letter)) || ((line < (c->sz - 1)) && iswhite(c, (line + 1), letter)))){
        return true;
    }
    return false;
}

bool check_leftright(const crossword* c, int line, int letter)
{
    if (iswhite(c, line, letter) && (((letter != 0) && iswhite(c, line, (letter - 1))) || ((letter != (c->sz - 1)) && iswhite(c, line, (letter + 1))))){
        return true;
    }
    return false;
}

void check_white(const crossword* c, int line, int letter, int* cnt_white)
{
    if (iswhite(c, line, letter)){
        (*cnt_white)++;
    }
}

//BEWARE - MERGER STRING FUNCTION POSES MEMORY LEAK POTENTIAL
// the second thing that came to me that night might me how to initialise the strings that we are going to merge
void meet_conditions_for_aX_and_down(const crossword* c, char across[], char down[])
{
    int cnt_aX = 1, cnt_down = 1, cnt_num = 1;
    for (int line = 0; line < c->sz; line++){
        for (int letter = 0; letter < c->sz; letter++){
            //3 conditions :
            if (facross(c, line, letter) && fdown(c, line, letter)){
                fill_up_for_aX_and_down(down, &cnt_down, &cnt_num);
                fill_up_for_aX_and_down(across, &cnt_aX, &cnt_num);
                cnt_num++;
            }
            else if (fdown(c, line, letter)){
                fill_up_for_aX_and_down(down, &cnt_down, &cnt_num);
                cnt_num++;
            }
            else if (facross(c, line, letter)){
                fill_up_for_aX_and_down(across, &cnt_aX, &cnt_num);
                cnt_num++;
            }
        }
    }
}

bool facross(const crossword* c, int line, int letter)
{
    if ((letter == 0 || isblack(c, line, (letter - 1))) && iswhite(c, line, (letter +1)) && iswhite(c, line, letter)){
        return true;
    }
    return false;
}

bool fdown(const crossword* c, int line, int letter)
{
    if (((line == 0 || isblack(c, (line - 1), letter)) && iswhite(c, (line + 1), letter) && iswhite(c, line, letter)) && (line < (c->sz - 1))){
        return true;
    }
    return false;
}

bool iswhite(const crossword* c, int line, int letter)
{
    if (c->arr[line][letter] == ' ' || c->arr[line][letter] == '.'){
        return true;
    }

    return false;
}

bool isblack(const crossword* c, int line, int letter)
{
    if (c->arr[line][letter] == 'X' || c->arr[line][letter] == '*'){
        return true;
    }

    return false;
}

void merge_aX_and_down_into_str(char* str, char across[], char down[]) 
{
    int cnt_merger = 0;
    for (int letter = 0; across[letter]; letter++, cnt_merger++){
        str[cnt_merger] = across[letter];
    }
    str[cnt_merger] = '|';
    cnt_merger++;

    for (int letter = 0; down[letter]; letter++, cnt_merger++){
        str[cnt_merger] = down[letter];
    }
    str[cnt_merger] = '\0';
}

void fill_up_for_aX_and_down(char array[], int* cnt_ax_d, int* cnt_num){
    array[*cnt_ax_d] = '-'; 
    array[(*cnt_ax_d + 1)] = '0' + *cnt_num;
    *cnt_ax_d += 2;
}


// Convert crossword to string of across & down numbers
void getcluestring(const crossword* c, char* str)
{
// I assume that the second argument of the OR statement is not checked if the first one is correct
    char across[(BIGSTR * 2 + 1)] = {"A-"}, down[BIGSTR] = {"D-"};
    meet_conditions_for_aX_and_down(c, across, down); 
    merge_aX_and_down_into_str(str, across, down);
    //printf("merged is %s\n", str);
    //checking the lowest row simultaneously is impossible and unnecessary -> can create another function just to check the lowest row for across
}



/*
   Convert a size (sz) & string (ip) into a crossword*
   White squares are ' ' or '.', black squares 'X' or '*'
*/
bool str2crossword(int sz, char* ip, crossword* cw)
{   
    //find out what the problem was with this assertion assert(!str2crossword(1, NULL, &c));

    unsigned long int supposed_ip_len = sz*sz;
    if (sz < 1){
        return false;
    }   
    if (strlen(ip) != supposed_ip_len ){
        return false;
    }
    cw->sz = sz;
    oned_to_twod_array(ip, cw);
    return true;
}

void oned_to_twod_array(char* ip, crossword* cw){
    int ip_pos;
    for (int line = 0; line < cw->sz; line++){
        for (int sq_filler = 0; sq_filler < cw->sz; sq_filler++){
            ip_pos = line * (cw->sz) + sq_filler;
            cw->arr[line][sq_filler] = ip[ip_pos];
        }
    }
}

void square_two_d_arr_printer(int border, crossword* cw)
{
    for (int line = 0; line < border; line++){
        for (int letter = 0; letter < border; letter++){
            printf("%c", cw->arr[line][letter]);
        }
        printf("\n");
    }
}

void test(void)
{
    /*
    crossword c;
    str2crossword(3, "123456789", &c);
    
    char array[3][3] = {{"123"}, {"456"}, {"789"}};
    int border = 3;
    square_two_d_arr_printer(border, array);
    */

}
