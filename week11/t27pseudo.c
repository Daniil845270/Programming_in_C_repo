#include "t27.h"

// 'Internal' function prototypes 
// ...
void on_error(const char* s);
void* ncalloc(int n, size_t size);

dict* dict_init(void) 
{
    dict* p;
    p = array_node_init(p, NULL); // looks cursed, but it does the job

    return p;
}

void on_error(const char* s)
{
   fprintf(stderr, "%s\n", s);
   exit(EXIT_FAILURE);
}

void* ncalloc(int n, size_t size)
{
   void* v = calloc(n, size);
   if(v==NULL){
      on_error("Cannot calloc() space");
   }
   return v;
}

bool dict_addword(dict* p, const char* wd)
{
    foreplay functions:
        - isnull_dict(p)
        - isnull_cchar(wd)

        - if strlen(wd) == 0 return false // check with a TA
        - tolower(wd);
            //need to add the ctype.h library        
        - illegal_chars(wd)
            this function would traverse through the string and look if each chracter is permitted
            if it finds an illegal character, then it should return true
                    if (illegal_chars(wd) == true) return false //it is not stated anywhere specifically what to do in this case, but following 
                    //the logic of what the function should return, if it is not pollible to add a word, then the function shoudl return false
                    //maybe we can print something

            
    what do I want this function to do in plain English
    1) while (wd[i] != '\0')
        idx = char2idx(wd[i]) 
            char2idx is a function that takes in a single character and returns an integer (can also make it and unsigned short integer for no reason)
            I can create a hash table and populate is with indexes of the alphabet purely for the sake of understanding how that works
            But if I want to play it safe, I can just 
                1) check if the character is an apostrophe and return (ALPHA - 1)
                2) return an int of wd[i] - 'a'
        if (p->dwn[idx] == '\0'){ //need to not forget to figure out how to initialise the first node in the init fucntion 
            p = array_node_init(p->dwn[idx], p);
            
            p->dwn[idx] = (dict*) ncalloc(1, sizeof(dict));
            p->dwn[idx]->up = p;

        }

    //if the word is already in the dictionary, then return false, but increment the frequency

    return true;
}

dict* array_node_init(dict* arrP, dict* p)
{
    arrP = (dict*) ncalloc(1, sizeof(dict));
    arrP->up = p;
    arrP->terminal = false;
    arrP->freq = -1; // arbitrary number that should be typedefed
    return arrP;
}

void dict_free(dict** d)
{
    foreplay functions:
        - isnull_pdict(p)
}

int dict_wordcount(const dict* p)
{
    foreplay functions:
        - isnull_cdict(p)
}

int dict_nodecount(const dict* p)
{
    foreplay functions:
        - isnull_cdict(p)
}

dict* dict_spell(const dict* p, const char* str)
{
    foreplay functions:
        - isnull_cdict(p)
        - isnull_cchar(wd)
}

int dict_mostcommon(const dict* p)
{
    foreplay functions:
        - isnull_cdict(p)
}

// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2)
{
    foreplay functions:
        - isnull_dict(p)
        - isnull_dict(p)
}

// CHALLENGE2
void dict_autocomplete(const dict* p, const char* wd, char* ret)
{
    foreplay functions:
        - isnull_cdict(p)
        - isnull_cchar(wd)
        - isnull_cchar(wd)
}
