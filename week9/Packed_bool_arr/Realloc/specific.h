// #include "../boolarr.h"
#include <math.h>

#define BYTE 8
#define UCHR unsigned char
#define UINT unsigned int
#define BIGNUM 1000

struct boolarr {
   UCHR* bArr;
   UINT bytes;
   UINT idx;
   UINT used_bits;
};

typedef struct boolarr boolarr;
