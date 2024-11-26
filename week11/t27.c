#include "t27.h"
#include <ctype.h>
#define APOSTROPHE 39
#define BIGNUM 1000
#define SWAP(A,B) {char temp; temp=A;A=B;B=temp;}

enum action {wordCount, nodeCount, mostCommon};
typedef enum action action;

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

void rec_act(const dict* q, int* num, action todo);
void dic_free_recursion(dict* p);

bool is_uniq_unique(dict* uniq, char c);

dict* qstr_fillup(dict* q, char* str);
char idx2char(int idx);
void strrev(char* s, int start, int end);



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

dict* dict_init(void)
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
    if (dict_addword_gatekeep(p, wd) == true){ //does what it supposed to do
        return false;
    }

    int itr = 0;
    dict* q = p;
    dict* uniq = divergent_node(q, wd, &itr); // does what it supposed to do 

    if (is_uniq_unique(uniq, wd[itr]) == false){ //does what it supposed to do
        return false;
    }

    new_entry(uniq, wd, &itr);//does what it supposed to do
    return true;
}

bool is_uniq_unique(dict* uniq, char c)
{
    if ((uniq->terminal == true) && (c == 0)){
        (uniq->freq)++;
        return false;
    }
    return true;
}

dict* divergent_node(dict* q, const char* wd, int* itr)
{
    int idx;
    while (wd[*itr] != '\0'){
        idx = char2idx(wd[*itr]);
        if (q->dwn[idx] == NULL){
            // printf("Exit\n");
            return q;
        }
        // printf("Shound be herre\n");
        q = q->dwn[idx];  
        (*itr)++;
    }
    return q;
}

void new_entry(dict* uniq, const char* wd, int* itr)
{
    int idx;
    while (wd[*itr] != '\0'){ //so even in the situation of putting cart and then car into this dictionary, when putting car, it won't enter a loop, but would mark the node as terminal 
        // printf("Infinite loop\n");
        idx = char2idx(wd[*itr]);
        dict* uniq_temp = array_node_init(uniq->dwn[idx], uniq);
        uniq_temp->up = uniq;
        uniq->dwn[idx] = uniq_temp;
        uniq = uniq_temp;
        (*itr)++;
    }
    uniq->terminal = true;
    uniq->freq = 1;
}

int char2idx(char c) 
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
            // rec_act(q, NULL, myfree);
            *d = NULL;
        }
    }
}

void dic_free_recursion(dict* q) //yes, this is literally carbon copy of the beginning of rec_act(), but I didn't figure out how to get around freeing a constand dict*
{
    for (int node = 0; node < ALPHA; node++){
        if (q->dwn[node] != NULL){
            dic_free_recursion(q->dwn[node]);
        }
    }
    free(q);
}

void rec_act(const dict* q, int* num, action todo)
{
    for (int node = 0; node < ALPHA; node++){
        if (q->dwn[node] != NULL){
            rec_act(q->dwn[node], num, todo);
        }
    }
    switch (todo){
        case wordCount: 
            if (q->terminal){
                (*num) += q->freq;
            } break;
        case nodeCount:
            (*num)++; break;
        case mostCommon:
            if (q->terminal){
                if (q->freq > (*num)){
                    *num = q->freq;
                }
            } break;
        default: printf("This is unusual\n"); break;
    }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int dict_wordcount(const dict* p) //need to merge the recursive functions
{
    if (isnull_dict(p) == true){
        return 0; //it's a sensible return since a null pointer contains no words
    }

    int cnt = 0;

    // wordcount_rec(p, &cnt);
    rec_act(p, &cnt, wordCount);

    return cnt;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int dict_nodecount(const dict* p) //need to merge the recursive functions
{
    if (isnull_dict(p) == true){
        return 0; //it's a sensible return since a null pointer contains no nodes
    }

    int cnt = 0;

    // nodecount_rec(p, &cnt);
    rec_act(p, &cnt, nodeCount);

    return cnt;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

dict* dict_spell(const dict* p, const char* str) // test this function, there is a problem here
{
    if (isnull_dict(p) || isnull_cchar(str)){
        return NULL;
    }

    if (strlen(str) == 0){
        return NULL;
    }

    dict* q = p->dwn[(char2idx(str[0]))];
    if (!q){
        return NULL;
    }
    q = q->up;


    dict* chq_nd;
    
    for (int ltr = 0; str[ltr]; ltr++){
    //the line below is absolutely not readable, but this line does the following: 
    //1) look at the characters of the string you want to check in the dictionary 
    //2) convert the character into the index, that letters are stored in the array 
        //of characters in a node (i.e. a is 0 -> z is 25 and ' is 26) 
    //3) assinging the value of the pointer from the array of poiters into the original poitner (i.e. pointer chase)
        chq_nd = q->dwn[(char2idx(str[ltr]))];
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
        return 0; //it's a sensible return since a null pointer contains no words
    }

    int max = 0;

    rec_act(p, &max, mostCommon);

    return max;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2)
{
    if (isnull_dict(p1) || isnull_dict(p2)){
        printf("caught a null pointer\n");
        return 0;
    }

    dict* q1 = p1; dict* q2 = p2;
    char q1str[BIGNUM] = {0}; char q2str[BIGNUM] = {0};

    if (qstr_fillup(q1, q1str) != qstr_fillup(q2, q2str)){
        printf("nodes belong to different dictionaries\n");
        return 0;
    }
    
    strrev(q1str, 0, strlen(q1str)-1);
    strrev(q2str, 0, strlen(q2str)-1);

    printf("q1str: %s \n", q1str);
    printf("q2str: %s \n", q2str);
    printf("Was here\n");
    // if (q1str[0] != q2str[0]){ // return to this part later, when the main program works
    //     return -1;
    // }

    // printf("Was here\n");
    

    size_t dvrt = 0;
    while ((q1str[dvrt] == q2str[dvrt]) && (dvrt < strlen(q1str))){
        dvrt++;
    }

    // printf("dvrt: %d\n", dvrt);
    // printf("ans = %ld\n", (strlen(q1str) + strlen(q2str) - ((dvrt) * 2)));

    int ans = strlen(q1str) + strlen(q2str) - ((dvrt) * 2);

    return ans;
}

//fucntion take from https://github.com/csnwc/Notes/blob/main/Code/ChapN/strrev_rec.c
void strrev(char* s, int start, int end)
{
   if(start >= end){
      return;
   }
   SWAP(s[start], s[end]);
   strrev(s, start+1, end-1);
}

dict* qstr_fillup(dict* q, char* str)
{
    int loc = 0;
    int idx = 0;
    dict* ltr = NULL;
    while (q->up != NULL){
        idx = 0;
        ltr = q;
        q = q->up;

        while (q->dwn[idx] != ltr){
            idx++;
        }

        str[loc] = idx2char(idx);
        loc++;
    }
    return q;
}

char idx2char(int idx)
{
    if (idx == (ALPHA - 1)){
        return APOSTROPHE;
    }
    else{
        return (idx + 'a');
    }
}



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// // CHALLENGE2
// void dict_autocomplete(const dict* p, const char* wd, char* ret)
// {
// }

void test(void)
{
    dict* d = NULL;
    dict* e = NULL;
    dict* f = NULL;
    dict* g = NULL;
    dict* nullP = NULL;

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

    int num = 0;
    assert(divergent_node(d, "AbC'XyZ", &num) == d);
    assert(is_uniq_unique(d, 'A') == true);

    new_entry(d, "AbC'XyZ", &num);
    num = 0;
    dict* diverge = divergent_node(d, "AbC'XyZ", &num);
    // printf("%d\n", diverge->terminal);
    assert(is_uniq_unique(diverge, '\0') == false);
    // printf("%d\n", diverge->freq);
    // printf("%d\n", )
    // assert(is_uniq_unique() == false);
    dict_free(&d);

    //what if we feed some garbage data into these functions?
    g = dict_init();
    assert(dict_wordcount(g) == 0);
    assert(dict_mostcommon(g) == 0);
    assert(dict_nodecount(g) == 1); 

    assert(dict_wordcount(nullP) == 0);
    assert(dict_mostcommon(nullP) == 0);
    assert(dict_nodecount(nullP) == 0); 
    //to be fair, i can't really think of ways to break these functions. They either work, or they don't


    e = dict_init();
    f = dict_init();
    assert(dict_addword(e, "AbC'XyZ") == true);
    assert(dict_addword(e, "eeeAbC'XyZ") == true);
    assert(dict_addword(e, "eeeAbC'XyZee") == true);
    assert(dict_addword(e, "ABCDE") == true);
    assert(dict_addword(e, "ACDE") == true);
    assert(dict_addword(e, "CAt") == true);
    assert(dict_addword(e, "CARes") == true);

    //edge cases for dict_spell
    assert(dict_spell(nullP, "ABCDE") == NULL);
    assert(dict_spell(e, NULL) == NULL);

    //string you try to spell is not in the dict
    assert(dict_spell(e, "NOTinDICTIONARY") == NULL);

    //string you try to spell is not in the dict alt 1
    assert(dict_spell(e, "eeeA") == NULL);

    //string you try to spell is not in the dict alt 2
    assert(dict_spell(e, "eeeAbC'XyZeee") == NULL);

    //the final letter is not terminal node 
    assert(dict_spell(e, "eeeAbC'XyZe") == NULL);

    //what if we try to speel an empty string
    assert(dict_spell(e, "") == NULL);
    

    // dict_cmp
    dict* q1 = dict_spell(e, "CAt");
    dict* q2 = dict_spell(e, "CARes");
    assert(dict_cmp(q1, q2)==4);
    assert(dict_cmp(q2, q1)==4);

    //same as previous tbh
    q1 = dict_spell(e, "ABCDE");
    q2 = dict_spell(e, "ACDE");
    assert(dict_cmp(q1, q2)==7);
    assert(dict_cmp(q2, q1)==7);

    //comparing 2 words withough branching
    q1 = dict_spell(e, "eeeAbC'XyZ");
    q2 = dict_spell(e, "eeeAbC'XyZee");
    assert(dict_cmp(q1, q2)==2);
    assert(dict_cmp(q2, q1)==2);

    //comparing the same word
    q1 = dict_spell(e, "eeeAbC'XyZee");
    assert(dict_cmp(q1, q2)==0);
    assert(dict_cmp(q2, q1)==0);

    //what if the 2 words are from 2 different dictionaries
    assert(dict_addword(e, "dictEword") == true);
    assert(dict_addword(f, "dictFword") == true);
    q1 = dict_spell(e, "dictEword");
    q2 = dict_spell(f, "dictFword");
    assert(dict_cmp(q1, q2) == 0);


    assert(dict_addword(e, "AbC'XyZ") == false);
    assert(dict_addword(e, "eeeAbC'XyZee") == false);
    assert(dict_addword(e, "AbC'Xy") == true);
    assert(dict_addword(e, "AbC'Xy") == false);
    assert(dict_addword(e, "eeeAbC'XyZee") == false);

    //at this stage, dict e contains 9 unique words, that only have been added once 
        // "AbC'XyZ" 2
        // "eeeAbC'XyZ"
        // "eeeAbC'XyZee" 3 - the most frequently added word
        // "ABCDE"
        // "ACDE"
        // "CAt"
        // "CARes"
        // "dictEword"
        // "AbC'Xy" 2

    assert(dict_wordcount(e) == (9 + 1 + 2 + 1)); //to account for all of the words that have been added mulpiple times
    assert(dict_mostcommon(e) == 3);
    assert(dict_nodecount(e) == (1+12+12+6+9)); // to account all of the branches

    dict_free(&e);
    dict_free(&f);
    dict_free(&g);

    printf("End of my tests\n");
    printf("\n");
}