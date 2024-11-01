#include "rot18.h"
#include <stdbool.h>
#define AB 26
#define ALL_NUMS 10
#define BIG_NUM 300
#define FST_NUM ('0')
#define HALF_AB 13
#define HALF_NUMS 5
#define LAST_NUM ('9')
#define LWR_AB_BGN ('a')
#define LWR_AB_END ('z')
#define NUM_END ('9')
#define NOT_BIG_NUM 30
#define STRING_END ('\0')
#define UPR_AB_BGN ('A')
#define UPR_AB_END ('Z')

bool isletter(int letter);
int letter_swap(int letter);
bool isnumber(int number);
int number_swap(int number);
void your_tests(void);
void spchar_loopcheck(char str1[], char str2[], int spchar, int spchar_fin);


void rot(char str[])
{
    int cnt = 0;
    while (str[cnt] != STRING_END)
    {
        if (isletter(str[cnt]) == true) 
        {
            str[cnt] = letter_swap(str[cnt]);
        }
        
        else if (isnumber(str[cnt]) == true)
        {
            str[cnt] = number_swap(str[cnt]);
        }
        cnt++;
    }
}

bool isletter(int letter)
{
    if ((letter >= UPR_AB_BGN && letter <= UPR_AB_END) 
     || (letter >= LWR_AB_BGN && letter <= LWR_AB_END))
    {
        return true;
    }
    return false; 
} 

int letter_swap(int letter)
{
    int new_letter = letter + HALF_AB, ab_bounds;
    if (letter <= UPR_AB_END)
    {
        ab_bounds = UPR_AB_END;
    }
    
    else
    {
        ab_bounds = LWR_AB_END;
    }
    
    if (new_letter > ab_bounds)
    {
        new_letter -= AB;
    }
    return new_letter;
}

bool isnumber(int number)
{
    if (number >= FST_NUM && number <= LAST_NUM)
    {
        return true;
    }
    return false; 
} 

int number_swap(int number)
{
    number += HALF_NUMS;
    if (number > NUM_END)
    {
        number -= ALL_NUMS;
    }
    return number;
}

void your_tests(void) // Repetitive code!
{
    char str1[NOT_BIG_NUM] = {0}, str2[NOT_BIG_NUM] = {0};
    //int cnt = 0;
    
    spchar_loopcheck(str1, str2, 0, '/');
    spchar_loopcheck(str1, str2, ':', '@');
    spchar_loopcheck(str1, str2, '[', '`');
    spchar_loopcheck(str1, str2, '{', 127);
    
    //this checks that the rot18 works as intended 

    char str3[BIG_NUM];
    strcpy(str3,        "a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 1 2 3 4 5 6 7 8 9 0");
    rot(str3);
    assert(strcmp(str3, "n o p q r s t u v w x y z a b c d e f g h i j k l m N O P Q R S T U V W X Y Z A B C D E F G H I J K L M 6 7 8 9 0 1 2 3 4 5") == 0);
    rot(str3);
    assert(strcmp(str3, "a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 1 2 3 4 5 6 7 8 9 0") == 0);
    
    //this checks the empty string case
    char str4[NOT_BIG_NUM];
    strcpy(str4,        "");
    rot(str4);
    assert(strcmp(str4, "") == 0);
    rot(str4);
    assert(strcmp(str4, "") == 0);
    
}
 
void spchar_loopcheck(char str1[], char str2[], int spchar, int spchar_fin)
{
    int fisrt_letter = 0;
    for (; spchar <= spchar_fin; spchar++)
    {
        str1[fisrt_letter] = spchar; str2[fisrt_letter] = spchar;
        rot(str1);
        assert(strcmp(str1, str2) == 0);
    }
} 
  


