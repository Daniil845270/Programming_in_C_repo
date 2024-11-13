#include "specific.h"
#include "../general.h"
#include "../boolarr.h"

//https://stackoverflow.com/questions/2525310/how-to-define-and-work-with-an-array-of-bits-in-c

/* All elements initialised to "0" */
boolarr* boolarr_init(void)
{
    boolarr* ba = (boolarr*) ncalloc(1, sizeof(boolarr));
    ba->bArr = (UCHR*) ncalloc(1, sizeof(UCHR)); // This is a 1 byte of memory set to 0
    ba->bytes = 0; //Hense, the size of the array in bytes is 1
    return ba;
}

/* Create boolarr based on string e.g. "1100001" */
boolarr* b2i(const char* str)
{
    // this should be a separate function
    if (str == NULL){
        on_error("Feeding a function with null pointer");
    }

    boolarr* ba = (boolarr*) ncalloc(1, sizeof(boolarr));

    if (strlen(str) == 0){ // I don't actually know what to return in the case when the str is empty
        return ba;
    }

    //this should be a separate function
    UINT bitcnt = 0;
    UINT bytecnt = 0;
    UINT b2inum = 0;
    UCHR temp[BIGNUM] = {0};
    
    idx = strlen(str) - 1;
    for (int i = 0; idx >= 0; idx--){
        if ((bitcnt == 7) || (idx == 0)){
            temp[bytecnt] = b2inum;
            bytecnt++;
            bitcnt = 0;
            b2inum = 0;
        }
        if (str[idx] == 0){
            bitcnt++;
        }
        else{
            b2inum = b2inum + pow(2, bitcnt);
            bitcnt++;
        }
    }

    //this should be a separate fucntion
    if (ba->bytes < strlen(temp)){
        ba->bArr = (UCHR*) nremalloc(ba->bArr, (sizeof(UCHR) * ((l->size + 1) + bytecnt)));
        ba->bytes = ba->bytes + bytecnt;
    }

    return ba;
}

/* Return a deep copy */
boolarr* boolarr_clone(const boolarr* ba)
{
    return ba;
}

/* Get number of bits in array */
unsigned int boolarr_size(const boolarr* ba)
{
    return 0;
}

/* Return number of bits that are set true */
unsigned int boolarr_count1s(const boolarr* ba)
{
    return 0;
}

/* Set nth bit on/off */
bool boolarr_set(boolarr* ba, const unsigned int n, const bool b)
{
    return true;
}

/* Get nth bit */
bool boolarr_get(const boolarr* ba, const unsigned int n, bool* b)
{
    return true;
}

/* Return if two arrays are the same (bitwise) */
bool boolarr_issame(const boolarr* b1, const boolarr* b2)
{
    return true;
}

/* Store to string - rightmost bit is LSB */
bool boolarr_tostring(const boolarr* ba, char* str)
{
    return true;
}

/* Print out array & meta info */
bool boolarr_print(const boolarr* ba)
{
    return true;
}

/* Flip all bits */
bool boolarr_negate(boolarr* ba)
{
    return true;
}

/* Functions dealing with 2 bitwise-arrays */
/* Must be the same length */
boolarr* boolarr_bitwise(const boolarr* ba1, const boolarr* ba2, const logicalop l)
{
    boolarr* ba;
    return ba;
}

/* Clears all space */
bool boolarr_free(boolarr* p)
{
    return true;
}
