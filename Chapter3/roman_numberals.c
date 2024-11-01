#include "rot18.h"
#define BIGSTR 1000

//int romantoarab(char romanltrs[]);
//void mytests(void);
int conv_adder(char romanltrs[], int cnt);
int conv_cubtractor(char romanltrs[], int cnt);
int roman_numberals(char romanltrs[]);
void my_tets(char romanltrs[]);

int main(void)
{
    char romanltrs[BIGSTR];
    my_tets(romanltrs);
    return 0;
}

void my_tets(char romanltrs[])
{

    strcpy(romanltrs, "III");
    assert(roman_numberals(romanltrs) == 3);
    strcpy(romanltrs, "VII");
    assert(roman_numberals(romanltrs) == 7);
    strcpy(romanltrs, "XIV");
    assert(roman_numberals(romanltrs) == 14);
    strcpy(romanltrs, "XXIX");
    assert(roman_numberals(romanltrs) == 29);
    strcpy(romanltrs, "XLIV");
    assert(roman_numberals(romanltrs) == 44);
    strcpy(romanltrs, "LVIII");
    assert(roman_numberals(romanltrs) == 58);
    strcpy(romanltrs, "LXXIII");
    assert(roman_numberals(romanltrs) == 73);
    strcpy(romanltrs, "LXXXIX");
    assert(roman_numberals(romanltrs) == 89);
    strcpy(romanltrs, "CXLIV");
    assert(roman_numberals(romanltrs) == 144);
    strcpy(romanltrs, "CCCXCIX");
    assert(roman_numberals(romanltrs) == 399);
    strcpy(romanltrs, "CDXLIV");
    assert(roman_numberals(romanltrs) == 444);
    strcpy(romanltrs, "DCCLXXXIX");
    assert(roman_numberals(romanltrs) == 789);
    strcpy(romanltrs, "MXXIV");
    assert(roman_numberals(romanltrs) == 1024);
    strcpy(romanltrs, "MMXXIII");
    assert(roman_numberals(romanltrs) == 2023);
    strcpy(romanltrs, "MMMCMXCIX");
    assert(roman_numberals(romanltrs) == 3999);

}

int roman_numberals(char romanltrs[])
{
    size_t num_size = strlen(romanltrs);
    int cnt = 0, arab_num = 0;
    arab_num += conv_adder(romanltrs, cnt);
    cnt++;
    while (cnt < num_size){
        arab_num += conv_adder(romanltrs, cnt);
        arab_num += conv_cubtractor(romanltrs, cnt);
        cnt++;
    }
    return arab_num;
} 

int conv_adder(char romanltrs[], int cnt)
{

    if (romanltrs[cnt] == 'I'){
        return 1;
    }
    else if (romanltrs[cnt] == 'V'){
        return 5;
    }
    else if (romanltrs[cnt] == 'X'){
        return 10;
    }
    else if (romanltrs[cnt] == 'L'){
        return 50;
    }
    else if (romanltrs[cnt] == 'C'){
        return 100;
    }
    else if (romanltrs[cnt] == 'D'){
        return 500;
    }
    else if (romanltrs[cnt] == 'M'){
        return 1000;
    }
    return 0; 
}

int conv_cubtractor(char romanltrs[], int cnt)
{
    if (romanltrs[(cnt - 1)] == 'I' && (romanltrs[(cnt)] == 'V' || romanltrs[(cnt)] == 'X')){
        return -2;
    }
    else if (romanltrs[(cnt - 1)] == 'X' && (romanltrs[(cnt)] == 'L' || romanltrs[(cnt)] == 'C')){
        return -20;
    }
    else if (romanltrs[(cnt - 1)] == 'C' && (romanltrs[(cnt)] == 'D' || romanltrs[(cnt)] == 'M')){
        return -200;
    }
    return 0;
}