#include "specific.h"
#include "../general.h"
#include "../boolarr.h"

//https://stackoverflow.com/questions/2525310/how-to-define-and-work-with-an-array-of-bits-in-c

/* All elements initialised to "0" */
boolarr* boolarr_init(void)
{
    boolarr* ba = (boolarr*) ncalloc(1, sizeof(boolarr));
    ba->Arr = (UCHR*) ncalloc(1, sizeof(UCHR)); // This is a 1 byte of memory set to 0
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
    UINT bits = 0;
    
    idx = strlen(str) - 1; // there is something wrong with this function
    for (int i = 0; idx >= 0; idx--){
        if (str[idx] == 0){
            bitcnt++;
        }
        else{
            b2inum = b2inum + pow(2, bitcnt);
            bitcnt++;
        }
        if ((bitcnt == 7) || (idx == 0)){
            temp[bytecnt] = b2inum;
            bytecnt++;
            bitcnt = 0;
            b2inum = 0;
        }
        bits++;
    }

    //this should be a separate fucntion
    if (ba->bytes < strlen(temp)){
        ba->Arr = (UCHR*) nremalloc(ba->Arr, (sizeof(UCHR) * ((l->size + 1) + bytecnt)));
        ba->bytes = ba->bytes + bytecnt;
    }
    ba->used_bits = bits;

    return ba;
}

/* Return a deep copy */
boolarr* boolarr_clone(const boolarr* ba)
{
    boolarr* cpy = (boolarr*) ncalloc(1, sizeof(boolarr));
    cpy->bArr = (UCHR*) ncalloc(1, sizeof(UCHR) * (ba->bytes + 1));
    memcpy(cpy->bArr, ba->Arr, ba->bytes); // this might be a problem
    return cpy;
}

/* Get number of bits in array */
unsigned int boolarr_size(const boolarr* ba)
{
    //write failsafes etc
    return (ba->used_bits); // or they might actually ask how many bits are in use -> need another variable in the structure
}

/* Return number of bits that are set true */
unsigned int boolarr_count1s(const boolarr* ba)
{
    //iterate thought the array
    //could create a table with all of the number-ones pair
    //create a loop that divides the number by 2^n where n is decrementing from 7 to 0. If num - 2^n > 0, there is a 1 in that position
    return 0;
}

/* Set nth bit on/off */
bool boolarr_set(boolarr* ba, const unsigned int n, const bool b)
{
    // byte = n / 8
    // idx = n - byte
    // if b is false, create a 11111111 mask with a 0 in the n position and AND it 
    // if b is true, create a 0000000 mask with a 1 in the n position and OR it 
    return true;
}

/* Get nth bit */
bool boolarr_get(const boolarr* ba, const unsigned int n, bool* b)
{
    // find the character you need
    // create a 0000000 mask with a 1 in the n position and AND it the number
    // if it is 0, than answer is false
    // otherwise it is true
    return true;
}

/* Return if two arrays are the same (bitwise) */
bool boolarr_issame(const boolarr* b1, const boolarr* b2)
{
    // if strcmp is null return true othwerwise flase
    return true;
}

/* Store to string - rightmost bit is LSB */
bool boolarr_tostring(const boolarr* ba, char* str)
{
    // figure out later
    return true;
}

/* Print out array & meta info */
bool boolarr_print(const boolarr* ba)
{
    // just a print function 
    return true;
}

/* Flip all bits */
bool boolarr_negate(boolarr* ba)
{
    //xor it with a mask 11111111 i think
    return true;
}

/* Functions dealing with 2 bitwise-arrays */
/* Must be the same length */
boolarr* boolarr_bitwise(const boolarr* ba1, const boolarr* ba2, const logicalop l)
{
    //this is the function to write before the bitwise ones
    boolarr* ba;
    return ba;
}

/* Clears all space */
bool boolarr_free(boolarr* p)
{
    //bunch of freeing
    return true;
}
