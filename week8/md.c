#include "mydefs.h"

bool file2str(const char* fname, char* str) // the length of the string is defined outside of the funciton and it is assumed that the length is enough. may need to put a failsafe here as well 
{
   if (fname == NULL || str == NULL){
      return false;
   }
   
   if (readNcheck_file(fname, str) == graceful_exit){
      return false;
   }
 
   return true;
}

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

state* str2state(const char* str) //adapt all of the same failsafes for this function from file2string, Neil will brake it 
{
   state* s = calloc(1, sizeof(state));

   //here are all of the barriers that break the funciton

   s->brdlist[0].clmn = 0;
   for (int letter = 2; str[letter] != '-'; letter++){
      (s->brdlist[0].clmn)++;
   }

   s->brdlist[0].rows = 0;
   for (int letter = 0; str[letter]; letter++){
      if (str[letter] == '-'){
         (s->brdlist[0].rows)++;
      }
   }

   s->brdlist[0].hawk = str[0];

   s->pcnt = 0;

   s->dcnt = 1;

   copy_strToState(&(s->brdlist[0]), str);
   // structarray_printer(&(s->brdlist[0]));

   // printf("s->brdlist[0].hawk = %c\n", s->brdlist[0].hawk);
   // printf("s->pcnt = %d\n", s->pcnt);
   // printf("s->dcnt = %d\n", s->dcnt);
   // printf("s->brdlist[0].clmn = %d\n", s->brdlist[0].clmn);
   // printf("s->brdlist[0].rows = %d\n", s->brdlist[0].rows);
   return s;
}

void copy_strToState(board* cpyboard, const char* str)
{
   int row = 0;
   int column = 0;
   for (int letter = 2; str[letter]; letter++){
      if (str[letter] == '-'){
         column = 0;
         row++;
      }
      else{
         cpyboard->brd[row][column] = str[letter];
         // printf("row = %d, column = %d\n", row, column);
         column++;
         // printf("%c", cpyboard->brd[row][column]);
      }
   }
}

void structarray_printer(board* b)
{
   for (int irow = 0; irow < b->rows; irow++){
      for (int col = 0; col < b->clmn; col++){
         printf("%c", b->brd[irow][col]);
      }
      printf("\n");
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* For a state s, returns the number of 'moves'
required to solve the board.
An already solved board=0
An impossible board=-1
If verbose==true, then print out the solution,
otherwise, print nothing.
*/


int solve(state* s, bool verbose)
{
   solv mysolution = find_solution(s);

   printf("\n");
   printf("Program finished\n");
   print_finstructarray(s);

   return 0;
}

void print_finstructarray(state* s)
{
   for (int struc = 1; struc <= s->dcnt; struc++){
      printf("Index = %d, hawk is %c\n", struc, s->brdlist[struc].hawk);
      structarray_printer(&(s->brdlist[struc]));
      printf("\n");
   }
}

solv find_solution(state* s)
{
   // int statrow = s->brdlist[0].rows;
   int statcol = s->brdlist[0].clmn;

   
   while (s->solved == false){ // while (s->solved == false){
      for (int col = 0; col < statcol; col++){
         create_dauthers(s, col);
         if (find_match(s) == differ){
            if (is_solution(s) == true){ 
               return solution_found;
            }
            (s->dcnt)++;
         }
         else{
            if ((s->dcnt == s->pcnt + 1) && (col == statcol- 1)){ // there may be an issue with this condition
               printf("solution_doesnt_exist\n");
               return solution_doesnt_exist;
            }
         }
      }
      (s->pcnt)++;
   }
   return 0;
}



bool is_solution(state* s)
{
   int di = s->dcnt;
   // int pi = s->pcnt;
   int frow = s->brdlist[0].rows;
   int fcol =  s->brdlist[0].clmn;

   // for (int row = frow - 1; row > 0; row--){
   //    if (s->brdlist[di].brd[row][col] != s->brdlist[di].brd[(row - 1)][col]){
   //       return false;
   //    }
   // }

   for (int col = 0; col < fcol; col++){
      for (int row = frow - 1; row > 0; row--){
         if (s->brdlist[di].brd[row][col] != s->brdlist[di].brd[(row - 1)][col]){
            return false;
         }
      }
   }
   return true;
}

cmpr find_match(state* s)
{
   for (int strc = 0; strc < s->dcnt; strc++){
      if (comparator(s, strc) == same){
         return same;
      }
   }
   return differ;
}

cmpr comparator(state* s, int strc)
{
   int di = s->dcnt;
   // int pi = s->pcnt;
   int statrow = s->brdlist[0].rows;
   int statcol = s->brdlist[0].clmn;

   for (int row = 0; row < statrow; row++){
      for (int col = 0; col < statcol; col++){
         if (s->brdlist[strc].brd[row][col] != s->brdlist[di].brd[row][col]){
            return differ;
         }
      }
   }
   return same;
}

void create_dauthers(state* s, int col)
{
   cpyParDtr(s);
   shift_tile(s, col);
   printf("create_dauthers\n");
   printf("s->dcnt is %d, s->brdlist[(s->dcnt)] is below\n", s->dcnt);
   structarray_printer(&(s->brdlist[(s->dcnt)]));

}

void shift_tile(state* s, int col)
{
   int di = s->dcnt;
   int pi = s->pcnt;
   int frow = s->brdlist[0].rows;
   // int fcol =  s->brdlist[0].clmn;
   s->brdlist[di].hawk = s->brdlist[di].brd[(frow - 1)][col];

   for (int row = frow - 1; row > 0; row--){
      s->brdlist[di].brd[row][col] = s->brdlist[di].brd[(row - 1)][col];
   }

   s->brdlist[di].brd[0][col] = s->brdlist[pi].hawk;
}

void cpyParDtr(state* s)
{
   int di = s->dcnt;
   int pi = s->pcnt;
   s->brdlist[di].parent = pi;
   int statrow = s->brdlist[di].rows = s->brdlist[0].rows;
   int statcol = s->brdlist[di].clmn = s->brdlist[0].clmn;

   for (int row = 0; row < statrow; row++){
      for (int col = 0; col < statcol; col++){
         s->brdlist[di].brd[row][col] = s->brdlist[pi].brd[row][col];
      }
   }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void test(void)
{
   char str[(BRDSZ*BRDSZ+BRDSZ+2)];
   state* s;

   // assert(file2str("2moves.brd", str));
   strcpy(str, "A-ABC-ABC-ABC-CBA"); //change back to A-ABC-ABC-ABC-CBA A-A-A-A-A-A-A S-ABC-BBC-CBC-DBA
   s = str2state(str);
   assert(s);
   solve(s, true);
   free(s);
   // printf("\n");

   strcpy(str, "A-ABCABC-ABCABC-ABCABC-CBACBA");
   s = str2state(str);
   assert(s);
   free(s);

   // printf("\n");

   strcpy(str, "A-A-A-A-A-A-A");
   s = str2state(str);
   assert(s);
   free(s);

   // printf("\n");

   strcpy(str, "A-AAAAAA-AAAAAA-AAAAAA-AAAAAA-AAAAAA-AAAAAA");
   s = str2state(str);
   assert(s);
   free(s);


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


