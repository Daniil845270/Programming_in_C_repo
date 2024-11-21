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
    quickcheck functions:
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

    int i = 0;
    uniq = divergent_node(p, wd, i);
    if (uniq->terminal == true){
        (uniq->freq)++;
        return false;
    }

    !!!!!!below should be a separate function, e.g. newEntry()!!!!!
    while (wd[i] != '\0')
        idx = char2idx(wd[i]) 
            char2idx is a function that takes in a single character and returns an integer (can also make it and unsigned short integer for no reason)
            I can create a hash table and populate is with indexes of the alphabet purely for the sake of understanding how that works
            But if I want to play it safe, I can just 
                1) check if the character is an apostrophe and return (ALPHA - 1)
                2) return an int of wd[i] - 'a'
        p = array_node_init(p->dwn[idx], p);
        idx++

    so after this loop, p is the last node of the word in the dictionaly, hence need to transofrm it into one
    p->terminal = true
    p->freq = 1;
    return true;
}

dict* divergent_node(dict* p, const char* wd, int i)
{
    while (wd[i] != '\0'){
        idx = char2idx(wd[i])
        if (p->dwn[idx] == NULL){
            return p;
        }
        idx++;
    }
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
    quickcheck functions:
        - isnull_pdict(d)

    dict* p = *d; //dereference the pointer to the pointer to the first node of the dictionary
    dic_free_recursion(p);
    *d = NULL;
}

void dic_free_recursion(dict* p) // this should work
{
    for (int i = 0; p->dwn[i]; i++){
        if (p->dwn[i] != NULL){
            dic_free_recursion(p->dwn[i]);
        }
    }
    free(p);
}

int dict_wordcount(const dict* p)
{
    quickcheck functions:
        - isnull_cdict(p)

    initialise the counter and set it to 1 (since p != NULL)
    create a recursion function, that is based on dic_free_recursion that (and pass an adress of the counter)
        finds terminal nodes (p->terminal == true)
        when the terminal node is found, increment the ecounter
}

int dict_nodecount(const dict* p)
{
    quickcheck functions:
        - isnull_cdict(p)

    this is literally dic_free_recursion, but with a counter 
}

dict* dict_spell(const dict* p, const char* str)
{
    quickcheck functions:
        - isnull_cdict(p)
        - isnull_cchar(wd)

    what does this function have to do again?
}

int dict_mostcommon(const dict* p)
{
    quickcheck functions:
        - isnull_cdict(p)

    adapt the recursive algorithm
}

// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2)
{
    quickcheck functions:
        - isnull_dict(p)
        - isnull_dict(p)

    

//it is probably a good idea to firslty check, if the two nodes are in the dictionary


    general idea:
    1) create 2 strings, one for p1 and one for p2 
    2) copy the pointers to q1 and q2 and fill up the p1 and p2 with pointers (while up != NULL)
    3) after the while loop, check the q1 and q2 are the same pointer
        what should you do if they are not?
}

// CHALLENGE2
void dict_autocomplete(const dict* p, const char* wd, char* ret)
{
    quickcheck functions:
        - isnull_cdict(p)
        - isnull_cchar(wd)
        - isnull_cchar(wd)
}
