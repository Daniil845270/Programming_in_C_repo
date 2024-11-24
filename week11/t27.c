#include "t27.h"
#include <ctype.h>
#define APOSTROPHE 39

// 'Internal' function prototypes 
dict* array_node_init(dict* arrP, dict* p);
void on_error(const char* s);
void* ncalloc(int n, size_t size);

bool dict_addword_gatekeep(dict* p, const char* wd);
bool illegal_chars(const char* wd);
bool isnull_dict(dict* p);
bool isnull_cchar(const char* wd);

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

dict* dict_init(void)
{
    dict* p = array_node_init(p, NULL); // looks cursed, but it does the job
    return p;
}

dict* array_node_init(dict* arrP, dict* p)
{
    arrP = (dict*) ncalloc(1, sizeof(dict));
    arrP->up = p;
    arrP->terminal = false;
    arrP->freq = -1; // arbitrary number that should be typedefed
    return arrP;
}

//taken from https://github.com/csnwc/ADTs/tree/main/General
void on_error(const char* s)
{
   fprintf(stderr, "%s\n", s);
   exit(EXIT_FAILURE);
}

//taken from https://github.com/csnwc/ADTs/tree/main/General 
void* ncalloc(int n, size_t size)
{
   void* v = calloc(n, size);
   if(v==NULL){
      on_error("Cannot calloc() space");
   }
   return v;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

bool dict_addword(dict* p, const char* wd)
{
    (dict_addword_gatekeep(p, wd) == true){
        return false;
    }

    int itr = 0;
    dict* q = p;
    uniq = divergent_node(q, wd, &itr);
    if (uniq->terminal == true){
        (uniq->freq)++;
        return false;
    }

    new_entry(uniq, wd, &itr);
    return true; // placeholder so that the compiler does not complain
}

void new_entry(dict* uniq, const char* wd, int* itr)
{
    while (wd[*itr] != '\0'){
        idx = char2idx(wd[i])
        uniq = array_node_init(uniq->dwn[idx], uniq);
    }
    uniq->terminal = true
    uniq->freq = 1;
}

dict* divergent_node(dict* q, const char* wd, int* itr)
{
    while (wd[*itr] != '\0'){
        idx = char2idx(wd[i])
        if (q->dwn[idx] == NULL){
            return q;
        }
        q = q->dwn[idx]; 
        (*itr)++;
    }
    return q;
}

int char2idx(char c) // need to check what are the actual values this function returns
{
    if (c == APOSTROPHE){
        return (ALPHA - 1);
    }
    else{
        return (tolower(c) - 'a');
    }
}

bool dict_addword_gatekeep(dict* p, const char* wd)
{
    if (isnull_dict(p) == true){
        return true; // which is stated in .h file
    }
    if (isnull_cchar(wd) == true){
        return true; // which is stated in .h file
    }
    if (strlen(wd) == 0){
        return true;
    }
    if (illegal_chars(wd) == true){
        return true;
    }
    return false;
}

bool illegal_chars(const char* wd) // maybe could do this with switch statements for fun, but later
{
    bool illegal;
    int ltr = 0;

    while (illegal = false && wd[ltr] != '\0'){
        illegal = true;
        if (wd[ltr] == APOSTROPHE){
            illegal = false;
        }
        else if (isupper(wd[ltr]) || islower(wd[ltr])){
            illegal = false;
        }
        ltr++;
    }

    if (illegal == true){
        return true;
    }
    return false;
}

bool isnull_dict(dict* p)
{
    if (p == NULL){
        return true;
    }
    return false;
}

bool isnull_cchar(const char* wd)
{
    if (wd == NULL){
        return true;
    }
    return false;
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void dict_free(dict** d)
{
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int dict_wordcount(const dict* p)
{
    return 0; // placeholder so that the compiler does not complain
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int dict_nodecount(const dict* p)
{
    return 0;// placeholder so that the compiler does not complain
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

dict* dict_spell(const dict* p, const char* str)
{
    dict* pp; // placeholder so that the compiler does not complain
    return pp; // placeholder so that the compiler does not complain
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int dict_mostcommon(const dict* p)
{
    return 0; // placeholder so that the compiler does not complain
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2)
{
    return 0; // placeholder so that the compiler does not complain
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// CHALLENGE2
void dict_autocomplete(const dict* p, const char* wd, char* ret)
{
}

void test(void)
{
}
