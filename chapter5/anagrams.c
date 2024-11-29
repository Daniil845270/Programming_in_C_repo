#include "headerfile.h"

// outline for the program:
// 1) bianry search would definitely be helpful

// 3) what do I actually need?
//     1) I need to use argc and argv, because the user writes arguments in the "% ./ anagram sternaig"
//         - write the failsafes eg if the user writes no words, or more than one word, or if it is not a string
//     2) write a program that would create all of the permutations of the string 
//     3) for each of the permuations, do a binary search or some shit through the dictionary
//         - if the word is present, return a word 
//         - if the word is abscent, the 2 pointers of the search must meet and return -1
//         - have to use linked lists, because I dont know the size of the array i.e. I dont know how many words will the program return in the end

struct permuation {
    char curr_word;
    int word_len;
    int permuation_max;
    int permuation_iteration;
    struct permuation* next;
};
typedef struct permuation permuation;


int argcv_check(int argc, char* argv[]);
void permuations(char* argv[]);



int main(int argc, char* argv[])
{
    if (argcv_check(argc, argv) != 0){
        return 1;
    }

    int argv1len = strlen(argv[1]) + 1;
    char* word = (char*) malloc(argv1len + 1);
    assert(word != NULL);
    strcpy(word, argv[1]);

    char** permuations

    // printf("argv1len = %d, word = %s\n", argv1len, word);
    
    free(word);
    return 0;
}

void permuations(char* argv[])
{

}

int argcv_check(int argc, char* argv[])
{

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argv[1] == NULL || strcmp(argv[1], "") == 0){ // accepted hello1, so could make 
    //a more strict filter of which characters are allowed (e.g. only upper and lowercase characters) and which aren't, 
    //but dunno if this game is worth the candles 
        fprintf(stderr, "Non-string argument entered\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}