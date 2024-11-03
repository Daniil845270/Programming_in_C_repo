#include "mydefs.h"

bool file2str(const char* fname, char* str) // the length of the string is defined outside of the funciton and it is ASSumed that the length is enough. may need to put a failsafe here as well 
{
   if (fname == NULL || str == NULL){
      return false;
   }
   
   if (readNcheck_file(fname, str) == graceful_exit){
      return false;
   }
 
   return true;
}

//more fclose to each of the if statements
myexit readNcheck_file(const char* fname, char* str)
{
   FILE* fp = fopen(fname, "r"); 
   if (fp != NULL){
      char temp[BIG_NUM] = {'0'};              // optimise this when the function is working
      int cnt = 0;
      if (fillcheck_hawk(fp, temp, str, &cnt) == ckpt_fail){
         fclose(fp); return graceful_exit;
      }
      POS rowlen = 0;
      if (fillcheck_fstbody(fp, temp, str, &cnt, &rowlen) == ckpt_fail){
         fclose(fp); return graceful_exit;
      }
      if (fillcheck_restbody(fp, temp, str, &cnt, &rowlen) == ckpt_fail){
         fclose(fp); return graceful_exit;
      }
      fclose(fp); return normal_operation;
   }
   return graceful_exit;
}

ckpt fillcheck_hawk(FILE* fp, char* temp, char* str, int* cnt)
{
   if (fscanf(fp, "%s", temp) != 1){
      return ckpt_fail;
   }
   if (strlen(temp) != 1){
      return ckpt_fail;
   }
   if (only_uprletter(temp) == ckpt_fail){
      return ckpt_fail;
   }
   line_fillup(temp, str, cnt);
   return ckpt_pass;
}

ckpt fillcheck_fstbody(FILE* fp, char* temp, char* str, int* cnt, POS* rowlen)
{
   if (fscanf(fp, "%s", temp) != 1){
      return ckpt_fail;
   }
   *rowlen = strlen(temp);
   // printf("strlen(temp) = %ld\n", strlen(temp));
   // printf("temp is %s.\n", temp);
   if (*rowlen < 1 || *rowlen > 6){
      return ckpt_fail;
   }
   if (only_uprletter(temp) == ckpt_fail){
      return ckpt_fail;
   }
   str[(*cnt)] = '-'; (*cnt)++;
   line_fillup(temp, str, cnt);
   return ckpt_pass;
}

ckpt fillcheck_restbody(FILE* fp, char* temp, char* str, int* cnt, POS* rowlen)
{
   int rowcnt = 1;
   while (fscanf(fp, "%s", temp) == 1){
      // printf("rowcnt = %d\n", rowcnt);
      if (rowcnt == 6){
         return ckpt_fail;
      }
      if (*rowlen != strlen(temp)){
         return ckpt_fail;
      }
      if (only_uprletter(temp) == ckpt_fail){
         return ckpt_fail;
      }
      str[(*cnt)] = '-'; (*cnt)++;
      line_fillup(temp, str, cnt); rowcnt++;
   }
   return ckpt_pass;
}

ckpt only_uprletter(char* temp)
{
   for (int letter = 0; temp[letter]; letter++){
      if (temp[letter] < 'A' || temp[letter] > 'Z'){
         return ckpt_fail;
      }
   }
   return ckpt_pass;
}

myexit line_fillup(char* temp, char* str, int* cnt)
{
   for (long unsigned int letter = 0; temp[letter]; letter++){
         str[(*cnt)] = temp[letter];
         (*cnt)++;
   }
   str[(*cnt)] = '\0';
   return normal_operation;
}


void test(void)
{
   char str[(BRDSZ*BRDSZ+BRDSZ+2)];
   // file2str("10moves.brd", str);
   // // printf("%s\n", str);
   assert(only_uprletter("ABCXYZ") == ckpt_pass);
   assert(only_uprletter("ABCXYz") == ckpt_fail);
   assert(only_uprletter("A") == ckpt_pass);
   assert(only_uprletter("@") == ckpt_fail);
   assert(only_uprletter("[") == ckpt_fail);
   assert(only_uprletter("!") == ckpt_fail);
   assert(only_uprletter("-") == ckpt_fail);

   // file2str first if testing
   assert(file2str(NULL, str) == false);
   assert(file2str("10moves.brd", NULL) == false);
   assert(file2str("nonexistent.brd", str) == false);

   // fillcheck_hawk testing
   assert(file2str("testempy.brd", str) == false);
   assert(readNcheck_file("testhawknobody.brd", str) == false);
   assert(readNcheck_file("testfalsehawknobody.brd", str) == false);

   // fillcheck_fstbody
   assert(readNcheck_file("testbadbody1.brd", str) == false);
   assert(readNcheck_file("testbadbody2.brd", str) == false);
   assert(readNcheck_file("testbadbody3.brd", str) == false);
   assert(readNcheck_file("testbadbody4.brd", str) == false);
   assert(readNcheck_file("testgood1row.c", str) == true);
   assert(strcmp("A-A", str) == 0);
   assert(readNcheck_file("testgood1row1.c", str) == true);
   assert(strcmp("A-AA", str) == 0);
   assert(readNcheck_file("testgood1row2.c", str) == true);
   assert(strcmp("A-AAAAA", str) == 0);
   assert(readNcheck_file("testgood1row3.c", str) == true);
   assert(strcmp("A-AAAAAA", str) == 0);

   assert(readNcheck_file("imposs_hasdash.brd", str) == false);

   assert(readNcheck_file("testgood2row.brd", str) == true);
   assert(strcmp("A-A-A", str) == 0);
   assert(readNcheck_file("testgood2row1.brd", str) == true);
   assert(strcmp("A-AA-AA", str) == 0);
   assert(readNcheck_file("testgood2row2.brd", str) == true);
   assert(strcmp("A-AAAAA-AAAAA", str) == 0);
   assert(readNcheck_file("testgood2row3.brd", str) == true);
   assert(strcmp("A-AAAAAA-AAAAAA", str) == 0);

   // // assert(readNcheck_file("testbad2row.brd", str) == false); //ask a question about this assert - I honestly don't know what to do with it
   // readNcheck_file("testbad2row.brd", str);
   // printf("%s\n", str);

   assert(readNcheck_file("testbad2row1.brd", str) == false);   
   assert(readNcheck_file("testbad2row2.brd", str) == false);
   assert(readNcheck_file("testbad2row3.brd", str) == false);
   assert(readNcheck_file("testbad2row4.brd", str) == false);
   assert(readNcheck_file("testbad2row5.brd", str) == false);
   assert(readNcheck_file("testbad2row6.brd", str) == false);

   assert(readNcheck_file("testgood3row.brd", str) == true);
   assert(strcmp("A-AAA-AAA-AAA", str) == 0);

   assert(readNcheck_file("testbad3row.brd", str) == false);
   assert(readNcheck_file("testbad3row1.brd", str) == false);
   assert(readNcheck_file("testbad3row2.brd", str) == false);
   assert(readNcheck_file("testbad3row3.brd", str) == false);
   assert(readNcheck_file("testbad3row4.brd", str) == false);
   // assert(readNcheck_file("testbad3row5.brd", str) == false);
   assert(readNcheck_file("testbad3row6.brd", str) == false);
   assert(readNcheck_file("testbad7row.brd", str) == false);  // accessing the 2d array out of bounds -> question: will str be set to what it is set in main or we have always have to check the accessing out of bounds

   assert(readNcheck_file("testgood6row.brd", str) == true);
   assert(strcmp("A-AAAAAA-AAAAAA-AAAAAA-AAAAAA-AAAAAA-AAAAAA", str) == 0);
}







// state* str2state(const char* str)
// {

//    // can actually copy some of the checks from file2str

//    // alloc space for state
//    // ...
//    // Put contents of string into
//    // first board of list in state.
//    // ...
//    // return state;
// }

// int solve(state* s, bool verbose)
// {
// }

// /* Many of other functions, as required */