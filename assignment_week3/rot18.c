//* Include the libraries in use*//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

//* declaring the function in use and naming it rot*//

 void rot18(void) {
//* creating the index and loop *//  

   int c, nl;
  nl = 0;
  
  while ((c = getchar()) != EOF) {
  //* moving the uppercase letters by 13 *//    

  if (c>= 'A' && c <= 'Z') {
      c = ((c - 'A' + 13) % 26) + 'A';
  }
   //* moving the lowercase letter by 13 *//

  else if (c >='a' && c <='z') {
          c = ((c - 'a'+13) % 26) + 'a';

//* moving the digits by 5 *//
          } else if(c >='0' && c <='9') {
              c = ((c - '0'+5) % 10) +'0';
          }

//* printing the variable *//
putchar(c);
}
    printf("%d\n", nl);
}
//* calling the rot function *//
int main() {
    rot18();
return 0;
}
