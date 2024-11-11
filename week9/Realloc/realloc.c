/*
A resizeable indexed array ADT. Here:
1. Setting an element out of bounds reallocs the array to make it valid
2. Getting an element out-of-bounds is an error
*/

typedef SCALEFACTOR 2
typedef INITSIZE 20

struct arr{
    int* myarr;
    int start;
    int end;
    int size;
};

/* Creates the empty array */
// the values of start and end are set to 0 by ncalloc anyway, which is containted in the general.c, so I'm good
arr* arr_init(void)
{
    arr* l = (arr*) ncalloc(1, sizeof(arr) * INITSIZE);
    arr->start = 0; //it is zero anyway, but just to make sure
    arr->end = INITSIZE - 1;
    arr->size = INITSIZE;
    return l;
}


/* Similar to l[n] = i, safely resizing if required */
void arr_set(arr *l, int n, int i)
{
    if (l){
        if (l->end <= n){
            l->myarr[n] = i;
        }
        else{
         // c->a = (colltype*) nremalloc(c->a, sizeof(colltype)*c->capacity*SCALEFACTOR);
            l->myarr = (arr*) nremalloc(l->myarr, sizeof(arr)*n);
            l->end = n; 
        }
    }
}


/* Similar to = l[n] */
int arr_get(arr *l, int n)
{

}
/* Clears all space used, and sets pointer to NULL */
void arr_free(arr **l)
{

}
