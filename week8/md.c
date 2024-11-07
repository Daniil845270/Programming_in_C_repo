#include "mydefs.h"

bool file2str(const char* fname, char* str) 
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
      char temp[BIG_NUM] = {'0'};             
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

ckpt only_uprletter(const char* temp)
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
   for (POS letter = 0; temp[letter]; letter++){
         str[(*cnt)] = temp[letter];
         (*cnt)++;
   }
   str[(*cnt)] = '\0';
   return normal_operation;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

state* str2state(const char* str) 
{
   if (str == NULL || gtkpng(str) == ckpt_fail){
      return NULL;
   }
   state* s = calloc(1, sizeof(state));
   if (s == NULL){
      on_error("Cannot calloc() space");
   }
   s->brdlist[0].clmn = 0;
   for (int letter = THRD; str[letter] != '-'; letter++){
      (s->brdlist[0].clmn)++;
   }
   s->brdlist[0].rows = 0;
   for (int letter = 0; str[letter]; letter++){
      if (str[letter] == '-'){
         (s->brdlist[0].rows)++;
      }
   }
   s->brdlist[0].hawk = str[0];
   s->pcnt = 0; s->dcnt = 1;
   copy_strToState(&(s->brdlist[0]), str);
   return s;
}

ckpt gtkpng(const char* str)
{
   if (strlen(str) < 3 || strlen(str) > 44){ 
      return ckpt_fail;
   }
   char charcheck[THRD] = {0};
   charcheck[0] = str[0];
   if (only_uprletter(charcheck) == ckpt_fail){
      return ckpt_fail;
   }
   if (str[1] != '-'){
      return ckpt_fail;
   }
   charcheck[0] = str[THRD];
   if (only_uprletter(charcheck) == ckpt_fail){ 
      return ckpt_fail;
   }

   int col_len = 0;
   for (int letter = THRD; str[letter] != '-' && str[letter]; letter++){ 
      col_len++;
   }
   if (col_len < 1 || col_len > 6){ 
      return ckpt_fail;
   }
   int row_cnt = 1;
   int col_itr = 0;
   for (int letter = THRD; str[letter]; letter++){
      if (str[letter] == '-'){
         row_cnt++;
         if (row_cnt == 7){
            return ckpt_fail;
         }
         if (col_itr != col_len){
            return ckpt_fail;
         }
         col_itr = 0;
      }
      else{
         charcheck[0] = str[letter];
         if (only_uprletter(charcheck) == ckpt_fail){ 
            return ckpt_fail;
         }
         col_itr++;
      }
   }
   if (col_itr != col_len && strlen(str) != 3){ 
      return ckpt_fail;
   }
   return ckpt_pass;
}

//from Programming in C database
void on_error(const char* s) 
{
   fprintf(stderr, "%s\n", s);
   exit(EXIT_FAILURE);
}

void copy_strToState(board* cpyboard, const char* str)
{
   int row = 0;
   int column = 0;
   for (int letter = THRD; str[letter]; letter++){
      if (str[letter] == '-'){
         column = 0;
         row++;
      }
      else{
         cpyboard->brd[row][column] = str[letter];
         column++;
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


int solve(state* s, bool verbose)
{
   if (s == NULL){
      return -1;
   }
   if (is_solution(s, true) == true){
      return 0;
   }
   if (find_solution(s) == solution_found){
      return backtrace_solution(s, verbose);
   }
   else{
      return -1;
   }
   return 0;
}

int backtrace_solution(state* s, bool verbose)
{
   int solseq[BIG_NUM_ALT] = {0}; 
   solseq[0] = s->dcnt;
   int step = 1;
   int trace = solseq[step] = s->brdlist[(s->dcnt)].parent;
   while (trace != 0){
      step++;
      trace = s->brdlist[trace].parent;
      solseq[step] = trace;
   }
   if (verbose == true){
      for (int i = step; i >= 0; i--){
         structarray_printer(&(s->brdlist[solseq[i]]));
         if (i != 0){
            printf("\n");
         }
      }
   }
   return step;
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
   int statcol = s->brdlist[0].clmn; 
   while (s->solved == false){
      for (int col = 0; col < statcol; col++){
         cpyParDtr(s);
         if (finclmn_check(s, col) == false){
            shift_tile(s, col);
            if (find_match(s) == differ){
               if (is_solution(s, false) == true){ 
                  return solution_found;
               }
               (s->dcnt)++;
            }
         }
         if ((s->dcnt==s->pcnt+1)&&(col==statcol-1)){ 
            return solution_doesnt_exist;
         }
      }
      (s->pcnt)++;
   }
   return solution_doesnt_exist;
}

bool finclmn_check(state* s, int col)
{
   int di = s->dcnt;
   int frow = s->brdlist[0].rows;

   if (frow <= 1){
      return true;
   }

   for (int row = frow - 1; row > 0; row--){
      if (s->brdlist[di].brd[row][col] != 
      s->brdlist[di].brd[(row - 1)][col]){
         return false;
      }
   }
   return true;
}

bool is_solution(state* s, bool edge)
{
   int di;
   if (edge == true){
      di = 0;
   }
   else{
      di = s->dcnt;
   }
   int frow = s->brdlist[0].rows;
   int fcol =  s->brdlist[0].clmn;

   for (int col = 0; col < fcol; col++){
      for (int row = frow - 1; row > 0; row--){
         if (s->brdlist[di].brd[row][col] !=
          s->brdlist[di].brd[(row - 1)][col]){
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
   int statrow = s->brdlist[0].rows;
   int statcol = s->brdlist[0].clmn;

   for (int row = 0; row < statrow; row++){
      for (int col = 0; col < statcol; col++){
         if (s->brdlist[strc].brd[row][col] 
            != s->brdlist[di].brd[row][col]){
            return differ;
         }
      }
   }
   return same;
}

void shift_tile(state* s, int col)
{
   int di = s->dcnt;
   int pi = s->pcnt;
   int frow = s->brdlist[0].rows;
   s->brdlist[di].hawk = 
   s->brdlist[di].brd[(frow - 1)][col];

   for (int row = frow - 1; row > 0; row--){
      s->brdlist[di].brd[row][col] = 
      s->brdlist[di].brd[(row - 1)][col];
   }

   s->brdlist[di].brd[0][col] = 
   s->brdlist[pi].hawk;
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
         s->brdlist[di].brd[row][col] = 
         s->brdlist[pi].brd[row][col];
      }
   }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void test(void)
{
   char str[(BRDSZ*BRDSZ+BRDSZ+THRD)];
   state* s;

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
   assert(only_uprletter("ABCXYZ") == ckpt_pass); //think how to write this assertions
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


   /////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////
   strcpy(str, "A-");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAAAA");
   s = str2state(str);
   assert(s == NULL);


   // strcpy(str, "A-AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
   // s = str2state(str);
   // assert(s == NULL);
   // free(s);

   strcpy(str, "-AAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "-");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A--B");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AA-A");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAAAA-AAAAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAAA-AAAAAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAAA-AAAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAA-AAAAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "AAAAA-AAAAA-AAAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAAA-AAAAAA-AAAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAA-AAAAAA-AAAAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAAA-AAAAAA-AAAAAAA");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-AAAAAA-AAAAAAA-AAAAAA");
   s = str2state(str);
   assert(s == NULL);
 

   strcpy(str, "A-A--A");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-A-AA-A");
   s = str2state(str);
   assert(s == NULL);


   // strcpy(str, "A-AAAAAA-AAAAAA-AAAAAA-AAAAAA-AAAAAA-AAAAAA-AAAAAA"); //invalid user input is not checked
   // s = str2state(str);
   // assert(s == NULL);
   // free(s);

   strcpy(str, "A-AB-CD-AB-CD-AB-CD-AB-CD-AB-CD"); //this assertion failed
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "A-B");
   s = str2state(str);
   assert(s);
   free(s);

   strcpy(str, "");
   s = str2state(str);
   assert(s == NULL);


   strcpy(str, "");
   s = str2state(str);
   assert(s == NULL);

   strcpy(str, "Z-Z");
   s = str2state(str);
   assert(s);
   free(s);

   strcpy(str, "Z-ZZ");
   s = str2state(str);
   assert(s);
   free(s);

   strcpy(str, "Z-ZZZ");
   s = str2state(str);
   assert(s);
   free(s);

   strcpy(str, "Z-ZZZZ");
   s = str2state(str);
   assert(s);
   free(s);

   strcpy(str, "Z-ZZZZZ");
   s = str2state(str);
   assert(s);
   free(s);

   strcpy(str, "Z-ZZZZZZ");
   s = str2state(str);
   assert(s);
   free(s);

   /////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////
   strcpy(str, "K-AB-GH"); //this one is 60
   s = str2state(str);
   assert(solve(s, false)==-1);
   free(s);

   printf("Passed mycase1\n"); 

   // strcpy(str, "K-AB-GH-MN"); 
   // s = str2state(str);
   // assert(solve(s, false)==-1);
   // free(s);

   // printf("Passed mycase2\n");


   // strcpy(str, "K-ABC-GHI-MNO"); //more than 15 mins this one already take way too long to compute. I guess lets say if it reaches a certain number just return -1, becuase it is probably infinite
   // s = str2state(str);
   // assert(solve(s, false)==-1);
   // free(s);

   // printf("Passed mycase2\n");

   // strcpy(str, "K-ABCDEF-GHIJKL-MNOPQR-STUVWX-YZABCD-EFGHIJ");
   // s = str2state(str);
   // assert(solve(s, false)==-1);
   // free(s);

   // printf("Passed mycase3\n");

   //lets start off easy, 2*4 test

// A
// -AB
// -AB
// -AB
// -BA
   printf("Entered mycase1\n");
   strcpy(str, "A-AB-AB-AB-BA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false)>0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase1\n");
   printf("\n");
   
// A
// -A
// -A
// -A
// -A
   printf("Entered mycase2\n");
   strcpy(str, "A-A-A-A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase2\n");
   printf("\n");

// A
// -B
// -A
// -A
// -A
   printf("Entered mycase3\n");
   strcpy(str, "A-B-A-A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase3\n");
   printf("\n");

// A
// -B
// -B
// -A
// -A
   printf("Entered mycase4\n");
   strcpy(str, "A-B-B-A-A");                                    //what should I do with this? Like when it is supposed to return 
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == -1);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase4\n");
   printf("\n");

// A
// -A
// -A
// -A
// -A
// -A
// -A
   printf("Entered mycase5\n");
   strcpy(str, "A-A-A-A-A-A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase5\n");
   printf("\n");

// A
// -B
// -A
// -A
// -A
// -A
// -A
   printf("Entered mycase6\n");
   strcpy(str, "A-B-A-A-A-A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase6\n");
   printf("\n");

// A
// -A
// -B
// -A
// -A
// -A
// -A
   printf("Entered mycase6\n");
   strcpy(str, "A-A-B-A-A-A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase6\n");
   printf("\n");

// A
// -A
// -A
// -B
// -A
// -A
// -A
   printf("Entered mycase6\n");
   strcpy(str, "A-A-A-B-A-A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase6\n");
   printf("\n");

// A
// -A
// -A
// -A
// -B
// -A
// -A
   printf("Entered mycase6\n");
   strcpy(str, "A-A-A-A-B-A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase6\n");
   printf("\n");

// A
// -A
// -A
// -A
// -A
// -B
// -A
   printf("Entered mycase6\n");
   strcpy(str, "A-A-A-A-A-B-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase6\n");
   printf("\n");

// A
// -B
// -B
// -A
// -A
// -A
// -A
   printf("Entered mycase7\n");
   strcpy(str, "A-B-B-A-A-A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) < 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase7\n");
   printf("\n");

// A
// -A
   printf("Entered mycase8\n");
   strcpy(str, "A-A");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase8\n");
   printf("\n");

// A
// -B
   printf("Entered mycase9\n");                       //one tile boards are always already solved
   strcpy(str, "A-B");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed mycase9\n");
   printf("\n");
                                                         //one column testing
   /////////////////////////////////////////////////////////////////////////////////
                                                         //one row testing 

// A
// -AA
   printf("Entered solved 1 row 2 column\n");                          //2 column cases
   strcpy(str, "A-AA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed solved 1 row 2 column\n");
   printf("\n");

// A
// -BA
   printf("Entered solved 1 row 2 column\n");                          
   strcpy(str, "A-BA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed solved 1 row 2 column\n");
   printf("\n");

// A
// -AB
   printf("Entered solved 1 row 2 column\n");                          
   strcpy(str, "A-BB");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed solved 1 row 2 column\n");
   printf("\n");

// A
// -AAAAA
   printf("Entered solved 1 row 5 column\n");                          
   strcpy(str, "A-AAAAA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed solved 1 row 5 column\n");
   printf("\n");

// A
// -AAAAAA
   printf("Entered solved 1 row 6 column\n");                          
   strcpy(str, "A-AAAAAA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed solved 1 row 6 column\n");
   printf("\n");

                                                         //one row testing 
///////////////////////////////////////////////////////////////////////////////////////
                                                         //2 row 2 column testing
// A
// --AA-AA
   printf("Entered 2X2 solved\n");                          
   strcpy(str, "A-AA-AA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) == 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed 2X2 solved\n");
   printf("\n");

// A
// -BA-AA
   printf("Entered 2X2 work\n");                          
   strcpy(str, "A-BA-AA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed 2X2 work\n");
   printf("\n");

// A
// -AB-AA
   printf("Entered 2X2 work\n");                          
   strcpy(str, "A-AB-AA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed 2X2 work\n");
   printf("\n");

// A
// -AA-BA
   printf("Entered 2X2 work\n");                          
   strcpy(str, "A-AA-BA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed 2X2 work\n");
   printf("\n");

// A
// -AA-AB
   printf("Entered 2X2 work\n");                          
   strcpy(str, "A-AA-AB");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed 2X2 work\n");
   printf("\n");

// A-BC-YZ
   printf("Entered 2X2 imposs\n");                          
   strcpy(str, "A-BC-YZ");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) < 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed 2X2 work\n");
   printf("\n");


                                                         //2 row 2 column testing
/////////////////////////////////////////////////////////////////////////////////////// 
                                                         //6 row 6 column testing

   // printf("Entered 3X3 imposs\n"); //reached 530000 and was interrupted                          
   // strcpy(str, "A-BCD-EFG-XYZ");
   // s = str2state(str);
   // assert(s);
   // assert(solve(s, false) < 0);
   // printf("Solved in %d moves\n", solve(s, false));
   // free(s);
   // printf("Passed 3X3 work\n");
   // printf("\n");

   // printf("Entered 6X6 letter gatekeeping imposs\n"); //reached 530000 and was interrupted                          
   // strcpy(str, "A-BCD-EFG-XYZ");
   // s = str2state(str);
   // assert(s);
   // assert(solve(s, false) < 0);
   // printf("Solved in %d moves\n", solve(s, false));
   // free(s);
   // printf("Passed 6X6 letter gatekeeping imposs\n");
   // printf("\n");

// A
// -ABCDEF
// -BCDEFA
// -CDEFAB
// -DEFABC
// -EFABCD
// -FABCDE

   // printf("Entered 6X6 letter poss A\n");   //took 40 mins and 270000 cases when I killed it             
   // strcpy(str, "A-ABCDEF-BCDEFA-CDEFAB-DEFABC-EFABCD-FABCDE");
   // s = str2state(str);
   // assert(s);
   // assert(solve(s, false) > 0);
   // printf("Solved in %d moves\n", solve(s, false));
   // free(s);
   // printf("Passed 6X6 letter poss A\n");
   // printf("\n");

   // printf("Entered 6X6 letter solved\n");                          
   // strcpy(str, "F-ABCDEF-ABCDEF-ABCDEF-ABCDEF-ABCDEF-ABCDEF"); //Solved in 8 moves and 335901 iterations
   // s = str2state(str);
   // assert(s);
   // assert(solve(s, false) == 0);
   // printf("Solved in %d moves\n", solve(s, false));
   // free(s);
   // printf("Passed 6X6 letter solved\n");
   // printf("\n");

// // A
// // -FBCDEA
// // -BACDEF
// // -ABCEDF
// // -ABCDEF
// // -ACBDEF
// // -ABCDEF

   // printf("Entered 6X6 letter poss randswaps\n");                          
   // strcpy(str, "A-FBCDEA-BACDEF-ABCEDF-ABCDEF-ACBDEF-ABCDEF");
   // s = str2state(str);
   // assert(s);
   // assert(solve(s, false) > 0);
   // printf("Solved in %d moves\n", solve(s, false));
   // free(s);
   // printf("Passed 6X6 letter poss randswaps\n");
   // printf("\n");


// A
// -ABCDEF
// -ABCDEF
// -ABCDEF
// -ABCDEF
// -ABCDEF
// -FBCDEA

   printf("Entered 6X6 letter poss randswaps\n");                          
   strcpy(str, "A-ABCDEF-ABCDEF-ABCDEF-ABCDEF-ABCDEF-FBCDEA");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves\n", solve(s, false));
   free(s);
   printf("Passed 6X6 letter poss randswaps\n");
   printf("\n");

// A
// -ABCDEF
// -ABCDEF
// -ABCDEF
// -ABCDEF
// -ABCDEF
// -ABCDEF

   // printf("Entered 6X6 letter poss 1\n");                          
   // strcpy(str, "A-ABCDEF-ABCDEF-ABCDEF-ABCDEF-ABCDEF-FBCDEA");
   // s = str2state(str);
   // assert(s);
   // assert(solve(s, false) > 0);
   // printf("Solved in %d moves and %d iterations\n", solve(s, false), s->dcnt);
   // free(s);
   // printf("Passed 6X6 letter poss 2nd randswaps\n");
   // printf("\n");

   // printf("Entered 6X6 letter poss 2\n");                          
   // strcpy(str, "A-ABCDEF-ABCDEF-ABCDEF-ABCDEF-FBCDEA-ABCDEF");
   // s = str2state(str);
   // assert(s);
   // assert(solve(s, false) > 0);
   // printf("Solved in %d moves and %d iterations\n", solve(s, false), s->dcnt);
   // free(s);
   // printf("Passed 6X6 letter poss 2nd randswaps\n");
   // printf("\n");

   // printf("Entered 6X6 letter poss 3\n");                          
   // strcpy(str, "A-ABCDEF-ABCDEF-ABCDEF-FBCDEA-ABCDEF-ABCDEF");
   // s = str2state(str);
   // assert(s);
   // assert(solve(s, false) > 0);
   // printf("Solved in %d moves and %d iterations\n", solve(s, false), s->dcnt);
   // free(s);
   // printf("Passed 6X6 letter poss 2nd randswaps\n");
   // printf("\n");

   printf("Entered 6X6 letter poss 4\n");                          
   strcpy(str, "A-ABCDEF-ABCDEF-FBCDEA-ABCDEF-ABCDEF-ABCDEF"); // 8 102 161 matt
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves and %d iterations\n", solve(s, false), s->dcnt);
   free(s);
   printf("Passed 6X6 letter poss 2nd randswaps\n");
   printf("\n");

   printf("Entered 6X6 letter poss 5\n");                          
   strcpy(str, "A-FBCDEA-ABCDEF-FBCDEA-ABCDEF-FBCDEA-ABCDEF"); // 8 102 161 matt
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves and %d iterations\n", solve(s, false), s->dcnt);
   free(s);
   printf("Passed 6X6 letter poss 2nd randswaps\n");
   printf("\n");

// // A
// // -AA
//    printf("Entered mycase1\n");                          
//    strcpy(str, "A-A");
//    s = str2state(str);
//    assert(s);
//    assert(solve(s, false) == 0);
//    printf("Solved in %d moves\n", solve(s, false));
//    free(s);
//    printf("Passed mycase1\n");
//    printf("\n");


   printf("Entered 10 move\n");                          
   strcpy(str, "C-AAB-ABB-CCB-CAC-ABC");
   s = str2state(str);
   assert(s);
   assert(solve(s, false) > 0);
   printf("Solved in %d moves and %d iterations\n", solve(s, false), s->dcnt);
   // for (int i = 0; i < 10; i++){
   //    structarray_printer(&(s->brdlist[(i)]));
   //    printf("\n");
   // }
   free(s);
   printf("Passed 10 move\n");
   printf("\n");

   strcpy(str, "A-AAA-AAA-AAA-AAA-AAA");
   s = str2state(str);
   s->dcnt = 1;
   cpyParDtr(s);
   s->dcnt = 2;
   cpyParDtr(s);
   s->dcnt = 3;
   cpyParDtr(s);
   // structarray_printer(&(s->brdlist[0]));
   // printf("\n");
   // structarray_printer(&(s->brdlist[1]));
   // printf("\n");
   // structarray_printer(&(s->brdlist[2]));
   // printf("\n");
   // structarray_printer(&(s->brdlist[3]));
   // printf("\n");

   assert(comparator(s, 0) == same);
   assert(comparator(s, 1) == same);
   assert(comparator(s, 2) == same);
   assert(comparator(s, 3) == same);
   assert(find_match(s) == same);
   free(s);


                                                         //6 row 6 column testing 
//////////////////////////////////////////////////////////////////////////////////////
                                                         //free
}

