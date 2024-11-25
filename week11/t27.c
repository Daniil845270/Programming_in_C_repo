#include "t27.h"
#include <ctype.h>
#define APOSTROPHE 39

// 'Internal' function prototypes 
void on_error(const char* s);
void* ncalloc(int n, size_t size);
dict* array_node_init(dict* arrP, dict* p);


void new_entry(dict* uniq, const char* wd, int* itr);
dict* divergent_node(dict* q, const char* wd, int* itr);
int char2idx(char c);
bool dict_addword_gatekeep(dict* p, const char* wd);
bool illegal_chars(const char* wd);
bool isnull_dict(const dict* p);
bool isnull_cchar(const char* wd);

void dic_free_recursion(dict* p);

void wordcount_rec(const dict* q, int* cnt);

void nodecount_rec(const dict* q, int* cnt);

void mostcommon_rec(const dict* q, int* max);



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

dict* dict_init(void) // figure out why the short version doesn't work
{
    dict* arrP = NULL;
    arrP = array_node_init(arrP, NULL);
    return arrP;
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
    if (dict_addword_gatekeep(p, wd) == true){
        return false;
    }

    int itr = 0;
    dict* q = p;
    dict* uniq = divergent_node(q, wd, &itr);
    if (uniq->terminal == true){
        (uniq->freq)++;
        return false;
    }

    new_entry(uniq, wd, &itr);
    return true; // placeholder so that the compiler does not complain
}

void new_entry(dict* uniq, const char* wd, int* itr)
{
    int idx;
    while (wd[*itr] != '\0'){ //so even in the situation of putting cart and then car into this dictionary, when putting car, it won't enter a loop, but would mark the node as terminal 
        idx = char2idx(wd[*itr]);
        uniq = array_node_init(uniq->dwn[idx], uniq);
    }
    uniq->terminal = true;
    uniq->freq = 1;
}

dict* divergent_node(dict* q, const char* wd, int* itr)
{
    int idx;
    while (wd[*itr] != '\0'){
        idx = char2idx(wd[*itr]);
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

bool illegal_chars(const char* wd)
{
    bool illegal = false;
    int ltr = 0;

    while (((illegal == false) && (wd[ltr] != '\0')) == true){
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

bool isnull_dict(const dict* p)
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
    if (d != NULL){
        dict* q = *d; //dereference the pointer to the pointer to the first node of the dictionary
        if (q != NULL){
            dic_free_recursion(q);
            *d = NULL;
        }
    }
}

void dic_free_recursion(dict* q)
{
    for (int node = 0; node < ALPHA; node++){
        if (q->dwn[node] != NULL){
            dic_free_recursion(q->dwn[node]);
        }
    }
    free(q);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int dict_wordcount(const dict* p) //need to merge the recursive functions
{
    if (isnull_dict(p) == true){
        return 0; //check what do you actually need to return
    }

    int cnt = 0;

    wordcount_rec(p, &cnt);

    return cnt;
}

void wordcount_rec(const dict* q, int* cnt)
{
    for (int node = 0; node < ALPHA; node++){ // in this loop we recursively going down to each terminal node
        if (q->dwn[node] != NULL){
            wordcount_rec(q->dwn[node], cnt); 
        }
    }
    if (q->terminal){
        (*cnt) += q->freq;
    }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int dict_nodecount(const dict* p) //need to merge the recursive functions
{
    if (isnull_dict(p) == true){
        return 0; //check what do you actually need to return
    }

    int cnt = 0;

    nodecount_rec(p, &cnt);

    return cnt;
}

void nodecount_rec(const dict* q, int* cnt)
{
    for (int node = 0; node < ALPHA; node++){ // in this loop we recursively going down to each terminal node
        if (q->dwn[node] != NULL){
            nodecount_rec(q->dwn[node], cnt); 
        }
    }
    (*cnt)++;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

dict* dict_spell(const dict* p, const char* str)
{
    if (isnull_dict(p) == true){
        return NULL; //check what do you actually need to return
    }
    if (isnull_cchar(str) == true){
        return NULL; //check what do you actually need to return
    }

    dict* q;
    dict* chq_nd;
    
    for (int ltr = 0; str[ltr]; ltr++){
//the line below is absolutely not readable, but this line does the following: 1) look at the characters of the string you want to check in the dictionary 2) convert the character into the index, that letters are stored in the array of characters in a node (i.e. a is 0 -> z is 25 and ' is 26) 3) assinging the value of the pointer from the array of poiters into the original poitner (i.e. pointer chase)
        chq_nd = p->dwn[(char2idx(str[ltr]))];
        if (chq_nd == NULL){
            return NULL;
        }
        q = chq_nd;
    }

//so once we reached the node, that contains the last node, we check if it is terminal
    if (q->terminal){
        return q;
    }
    else{
        return NULL;
    }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int dict_mostcommon(const dict* p) //need to merge the recursive functions
{
    if (isnull_dict(p) == true){
        return -1; //check what do you actually need to return
    }

    int max = 0;

    mostcommon_rec(p, &max);

    return max;
}

void mostcommon_rec(const dict* q, int* max) //this is almost copy&paste of wordcount_rec. Need to merge the functions
{
    for (int node = 0; node < ALPHA; node++){
        if (q->dwn[node] != NULL){
            mostcommon_rec(q->dwn[node], max); 
        }
    }
    if (q->terminal){
        if (q->freq > (*max)){
            *max = q->freq;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// // CHALLENGE1
// unsigned dict_cmp(dict* p1, dict* p2)
// {
//     return 0; // placeholder so that the compiler does not complain
// }

// //////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////

// // CHALLENGE2
// void dict_autocomplete(const dict* p, const char* wd, char* ret)
// {
// }

void test(void)
{
    dict* d = NULL;
    // char str[50];
    // assert(isnull_dict(d) == true); // and other functions

    // d = dict_init();
    // printf("assigned d\n");
    // assert(dict_addword(d, "Hel'loaZ"));

    // free(d);

    assert(illegal_chars("AbC'XyZ") == false);
    assert(illegal_chars("+++++++++") == true);
    assert(illegal_chars("AbC'X+yZ") == true);
    assert(isnull_dict(NULL) == true);
    assert(isnull_cchar(NULL) == true);
    assert(char2idx('a') == 0);
    assert(char2idx('A') == 0);
    assert(char2idx('z') == 25);
    assert(char2idx('Z') == 25);
    assert(char2idx(39) == 26); //there is no way to test an apostrophe as a letter 

    assert(dict_addword_gatekeep(d, "AbC'XyZ") == true);
    d = dict_init();
    assert(dict_addword_gatekeep(d, NULL) == true);
    assert(dict_addword_gatekeep(d, "") == true);
    assert(dict_addword_gatekeep(d, "+++++++++") == true);
    assert(dict_addword_gatekeep(d, "AbC'X+yZ") == true);

    dict_free(&d);


    printf("End of my tests\n");
    printf("\n");
}