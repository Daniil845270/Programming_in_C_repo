#include "rot18.h"
#define BIG_NUM 1000
#define CODE1_STRLEN 4
#define CODE2_STRLEN 8
#define CODE3_STRLEN 2
#define CODE4_STRLEN 1
#define CODE5_STRLEN 2
#define CODE6_STRLEN 1
int soundex_code(char surname[], int surname_cnt);
bool code1(char surname[], int letter);
bool code2(char surname[], int letter);
bool code3(char surname[], int letter);
bool code4(char surname[], int letter);
bool code5(char surname[], int letter);
bool code6(char surname[], int letter);

/*
struct codes {
    int code_num;
    char code_str[];
    int code_strlen;
}

typedef struct codes codes;
*/

int main(void)
{
    char surname[BIG_NUM] = {"Washington"};
    size_t surname_len = strlen(surname);
    char surname_code[4] = {'0'};
    surname_code[0] = surname[0]; //add toupper function
    int buffer_num, code_cnt = 1, surname_cnt = 1;
    while (code_cnt < 4 && surname_cnt < surname_len ){
        buffer_num = soundex_code(surname, surname_cnt);
        if (surname_code[(code_cnt - 1)] != buffer_num){
            surname_code[code_cnt] = buffer_num;
            code_cnt++;
        }
        surname_cnt++;
    }
    printf("%s\n", surname_code); //it actually should be 3, but 4 is also ok
    return 0;
    //need to not forget the case where the resulting code is shorder than the surname 
}
//this issue of nesting the functions is easily avoidable with 2-arrays

int soundex_code(char surname[], int surname_cnt)
{//i need the toupper function here!
    if (code1(surname, surname_cnt) == true){
        return 1;
    }
    else if (code2(surname, surname_cnt) == true){
        return 3;
    }
    else if (code3(surname, surname_cnt) == true){
        return 4;
    }
    else if (code4(surname, surname_cnt) == true){
        return 5;
    }
    else if (code5(surname, surname_cnt) == true){
        return 6;
    }
    else if (code6(surname, surname_cnt) == true){
        return 7;
    }
    printf("Something strange happened\n");
    return -1;
}

bool code1(char surname[], int letter)
{
    char code1_str[(CODE1_STRLEN + 1)] = {"BFPV"};
    for (int i = 0; i < CODE1_STRLEN; letter++){
        if (surname[letter] == code1_str[i]){
            return true;
        }
    }
    return false;
}

bool code2(char surname[], int letter)
{
    printf("was 2\n");
    char code2_str[(CODE2_STRLEN + 1)] = {"CGJKQSXZ"};
    for (int i = 0; i < CODE2_STRLEN; letter++){
        if (surname[letter] == code2_str[i]){
            return true;
        }
    }
    return false;
}
bool code3(char surname[], int letter)
{
    char code3_str[(CODE3_STRLEN + 1)] = {"DT"};
    for (int i = 0; i < CODE3_STRLEN; letter++){
        if (surname[letter] == code3_str[i]){
            return true;
        }
    }
    return false;
}
bool code4(char surname[], int letter)
{
    char code4_str[(CODE4_STRLEN + 1)] = {"L"};
    for (int i = 0; i < CODE4_STRLEN; letter++){
        if (surname[letter] == code4_str[i]){
            return true;
        }
    }
    return false;
}
bool code5(char surname[], int letter)
{
    printf("was 5\n");
    char code5_str[(CODE5_STRLEN + 1)] = {"MN"};
    for (int i = 0; i < CODE5_STRLEN; letter++){
        if (surname[letter] == code5_str[i]){
            return true;
        }
    }
    return false;
}
bool code6(char surname[], int letter)
{
    char code6_str[(CODE6_STRLEN + 1)] = {"R"};
    for (int i = 0; i < CODE6_STRLEN; letter++){
        if (surname[letter] == code6_str[i]){
            return true;
        }
    }
    return false;
}
