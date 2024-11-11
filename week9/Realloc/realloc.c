#include "specific.h"
/*
A resizeable indexed array ADT. Here:
1. Setting an element out of bounds reallocs the array to make it valid
2. Getting an element out-of-bounds is an error
*/


/* Creates the empty array */
// the values of start and end are set to 0 by ncalloc anyway, which is containted in the general.c, so I'm good
arr* arr_init(void)
{
    arr* l = (arr*) ncalloc(1, sizeof(arr));
    l->myarr = (int*) ncalloc(1, sizeof(int) * INITSIZE);
    l->size = INITSIZE;
    return l;
}

/* Similar to l[n] = i, safely resizing if required */
void arr_set(arr *l, int n, int i)
{
    if (l == NULL){
        on_error("Feeding a function with null pointer");
    }

    while ((l->size) < n){
        l->myarr = (int*) nremalloc(l->myarr, (sizeof(int) * l->size * SCALEFACTOR));
        l->size = l->size * SCALEFACTOR;
    }
    l->myarr[n] = i;
}

/* Similar to = l[n] */
int arr_get(arr *l, int n)
{
    if (l == NULL){
        on_error("Feeding a function with null pointer");
    }
    if (n >= l->size){
        on_error("Trying to access array out of bounds");
    }
    return (l->myarr[n]);
}

/* Clears all space used, and sets pointer to NULL */
void arr_free(arr **l)
{
    if (l == NULL){
        on_error("Feeding a function with null pointer");
    }
    free((*l)->myarr);
    free(*l);
    *l = NULL;
}
