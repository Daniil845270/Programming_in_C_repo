#include "rot18.h"
#define BIG_NUM 1000
void my_tests(char surname[], char surname_code[]);
int code_checker(int letter);
void code_filler(char surname[], char surname_code[5]);


int main(void)
{
    char surname[BIG_NUM] = {"Washington"};
    char surname_code[50] = {surname[0]};
    code_filler(surname, surname_code);
    printf("\n%s\n", surname_code);
    //printf("%li", strlen(surname_code));
    //my_tests(surname, surname_code);

    return 0;
}



void code_filler(char surname[], char surname_code[5])
{   
    int sur_cnt = 1;
    while (surname[sur_cnt]){
        if (code_checker(surname[sur_cnt]) == 6){
            int itr_cnt = sur_cnt;
            while(surname[itr_cnt] != '\0'){
                surname[itr_cnt] = surname[(itr_cnt + 1)]
                itr_cnt++;
            }
        }
        sur_cnt++
    }
    printf


    if (strlen(surname_code) < 4)
    {
        for (int i = 1; i < 4; i++){
            if (surname_code[i] == '\0'){
                surname_code[i] = '0';
            }
        }
    }
    surname_code[0] = surname[0];

}

int code_checker(int letter)
{
    
    char code_str[9][20] = {
        "BFPV",
        "CGJKQSXZ",
        "DT",
        "L",
        "MN",
        "R",
        "AEHIOU"
        "HWY",
        "\0"
    };
    int code;
    for (int i = 0; i < 9; i++){
        for (int j = 0; code_str[i][j]; j++){
            if (code_str[i][j] == toupper(letter)){
                code = i+1;
                //printf("Was here\n");
                return code;
            }
        }
    }
    code = 10;
    return code;
}


/*
    int sur_cnt = 1;
    int s_ccnt = 1;surname[sur_cnt]
    int buffer_index = code_checker(surname[1]);
    surname_code[0] = code_checker(surname[0]);
    while (surname[sur_cnt] && strlen(surname_code) < 4){
        while  (surname[sur_cnt] && 
               (code_checker(surname[(sur_cnt + 1)]) == 7 
            || code_checker(surname[(sur_cnt + 1)])) == 9){
            sur_cnt++; 
        }
        while (surname[sur_cnt] && (code_checker(surname[sur_cnt]) == code_checker(surname[(sur_cnt + 1)]))){
            sur_cnt++;
        }
        while (surname[sur_cnt] && ((strlen(surname) - sur_cnt - 1) > 2 
          && code_checker(surname[sur_cnt]) == code_checker(surname[(sur_cnt + 2)])
          && code_checker(surname[sur_cnt + 1]) == 7)){
            surname_code[s_ccnt] = '0' + buffer_index;
            s_ccnt += 1;
            sur_cnt += 3;
        }
        if (surname[sur_cnt] && strlen(surname_code)  <  4){
            surname_code[s_ccnt] = '0' + buffer_index;
            s_ccnt++;
            sur_cnt++;
        }

    }
    
*/

/*
#include "rot18.h"
#define BIG_NUM 1000
void my_tests(char surname[], char surname_code[]);
int code_checker(int letter);
void code_filler(char surname[], char surname_code[5]);


int main(void)
{
    char surname[BIG_NUM] = {"Pfister"};
    char surname_code[50] = {surname[0]};
    code_filler(surname, surname_code);
    printf("\n%s\n", surname_code);
    //printf("%li", strlen(surname_code));
    //my_tests(surname, surname_code);

    return 0;
}



void code_filler(char surname[], char surname_code[5])
{   
    bool repetition = false;
    int buffer_index;
    int s_ccnt = 1;
    for (int i = 1; surname[i]; i++){
        if (strlen(surname_code) < 4){
            buffer_index = code_checker(surname[i]);
            printf("buffer_index %i ", buffer_index);
            printf("surname_code %i\n", code_checker(surname_code[(s_ccnt - 1)]));
            if (repetition == false){
                if ((buffer_index + '0') != surname_code[(s_ccnt - 1)]){
                    repetition = true;
                }
                if (buffer_index != 7 && (buffer_index + '0') != surname_code[(s_ccnt - 1)]){
                    printf("Entry\n");
                    surname_code[s_ccnt] = '0' + buffer_index;
                    s_ccnt++;
                    //printf("surname_code %c ", surname_code[(s_ccnt - 1)]);
                    //printf("strlen %li ", strlen(surname_code));
                }
            }
            else{
                if (buffer_index != 7){
                    printf("Entry\n");
                    surname_code[s_ccnt] = '0' + buffer_index;
                    s_ccnt++;
                    repetition = false;
                }
            }
        }
    }

    if (strlen(surname_code) < 4)
    {
        for (int i = 1; i < 4; i++){
            if (surname_code[i] == '\0'){
                surname_code[i] = '0';
            }
        }
    }
    surname_code[0] = surname[0];

}

int code_checker(int letter)
{
    
    char code_str[6][10] = {
        "BFPV",
        "CGJKQSXZ",
        "DT",
        "L",
        "MN",
        "R"
    };
    int code;
    for (int i = 0; i < 6; i++){
        for (int j = 0; code_str[i][j]; j++){
            if (code_str[i][j] == toupper(letter)){
                code = i+1;
                //printf("Was here\n");
                return code;
            }
        }
    }
    code = 7;
    return code;
}

*/


/*
    bool repetition = false;
    surname_code[0] = code_checker(surname_code[0]);
    int buffer_index;
    int s_ccnt = 1;
    for (int i = 1; surname[i]; i++){
        if (strlen(surname_code) < 4){
            buffer_index = code_checker(surname[i]);
            printf("buffer_index %i ", buffer_index);
            printf("surname_code %i\n", code_checker(surname_code[(s_ccnt - 1)]));
            if (repetition == false){
                if ((buffer_index + '0') != surname_code[(s_ccnt - 1)]){
                    repetition = true;
                }
                if (buffer_index != 7 && (buffer_index + '0') != surname_code[(s_ccnt - 1)]){
                    printf("Entry\n");
                    surname_code[s_ccnt] = '0' + buffer_index;
                    s_ccnt++;
                    //printf("surname_code %c ", surname_code[(s_ccnt - 1)]);
                    //printf("strlen %li ", strlen(surname_code));
                }
            }
            else{
                if (buffer_index != 7){
                    printf("Entry\n");
                    surname_code[s_ccnt] = '0' + buffer_index;
                    s_ccnt++;
                    repetition = false;
                }
            }
        }
    }

*/










/*
void my_tests(char surname[], char surname_code[])
{
    strcpy(surname, "Washington");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "W252") == 0);

    strcpy(surname, "Wu");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "W000") == 0);

    strcpy(surname, "DeSmet");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "D253") == 0);

    strcpy(surname, "Gutierrez");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    //printf("\n%s\n", surname_code);
    assert(strcmp(surname_code, "G362") == 0);

    strcpy(surname, "Pfister");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "P236") == 0);

    strcpy(surname, "Jackson");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "J250") == 0);

    strcpy(surname, "Tymczak");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "T522") == 0);

    strcpy(surname, "Ashcraft");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "A261") == 0);
}


*/











































/*
#include "rot18.h"
#define BIG_NUM 1000
void my_tests(char surname[], char surname_code[]);
int code_checker(int letter);
void code_filler(char surname[], char surname_code[5]);


int main(void)
{
    char surname[BIG_NUM] = {"Tymczak"};
    char surname_code[50] = {surname[0]};
    code_filler(surname, surname_code);
    printf("\n%s\n", surname_code);
    //printf("%li", strlen(surname_code));
    //my_tests(surname, surname_code);

    return 0;
}



void code_filler(char surname[], char surname_code[5])
{
    int buffer_index;
    int s_ccnt = 1;
    for (int i = 1; surname[i]; i++){
        if (strlen(surname_code) < 4){
            buffer_index = code_checker(surname[i]);
            printf("buffer_index %i ", buffer_index);
            printf("surname_code %i\n", surname_code[(s_ccnt - 1)]);
            if (strlen(surname_code) == 1 && buffer_index == code_checker(surname_code[(s_ccnt - 1)])){
            }
            else if (buffer_index != 7 && (buffer_index + '0') != surname_code[(s_ccnt - 1)]){
                printf("Entry\n");
                surname_code[s_ccnt] = '0' + buffer_index;
                s_ccnt++;
                //printf("surname_code %c ", surname_code[(s_ccnt - 1)]);
                //printf("strlen %li ", strlen(surname_code));
            }
        }
    }

    if (strlen(surname_code) < 3)
    {
        for (int i = 1; i < 4; i++){
            if (surname_code[i] == '\0'){
                surname_code[i] = '0';
            }
        }
    }

}

int code_checker(int letter)
{
    
    char code_str[6][10] = {
        "BFPV",
        "CGJKQSXZ",
        "DT",
        "L",
        "MN",
        "R"
    };
    int code;
    for (int i = 0; i < 6; i++){
        for (int j = 0; code_str[i][j]; j++){
            if (code_str[i][j] == toupper(letter)){
                code = i+1;
                //printf("Was here\n");
                return code;
            }
        }
    }
    code = 7;
    return code;
}
*/
/*
void my_tests(char surname[], char surname_code[])
{
    strcpy(surname, "Washington");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "W252") == 0);

    strcpy(surname, "Wu");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "W000") == 0);

    strcpy(surname, "DeSmet");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "D253") == 0);

    strcpy(surname, "Gutierrez");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    //printf("\n%s\n", surname_code);
    assert(strcmp(surname_code, "G362") == 0);

    strcpy(surname, "Pfister");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "P236") == 0);

    strcpy(surname, "Jackson");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "J250") == 0);

    strcpy(surname, "Tymczak");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "T522") == 0);

    strcpy(surname, "Ashcraft");
    surname_code[0] = surname[0];
    surname_code[1] = '\0';
    surname_code[2] = '\0';
    surname_code[3] = '\0';
    code_filler(surname, surname_code);
    assert(strcmp(surname_code, "A261") == 0);
}


*/

























/*

void code_filler(char surname[], char surname_code[5])
{
    int buffer_index;
    int s_ccnt = 1;
    for (int i = 1; surname[i]; i++){
        buffer_index = code_checker(surname[i]);
        if (buffer_index != 7 && buffer_index != surname_code[(s_ccnt - 1)]){
            surname_code[s_ccnt] = '0' + buffer_index;
            s_ccnt++;
        }
    }
}

*/

        /*
        printf("buffer_index is %i\n", buffer_index);
        printf("surname_code[(s_ccnt - 1)] is %i\n", surname_code[(s_ccnt - 1)]);
        printf("surname_code is %s\n\n", surname_code);
        */