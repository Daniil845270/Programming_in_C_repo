#include "mydefs.h"

bool file2str(const char* fname, char* str)
{
   if (fname == NULL || str == NULL){
      return false;
   }

   // char filename_or_string[MAXSTR] = {'0'}; //don't need it
   if (readNcheck_file(fname, str) == graceful_exit){
      return false;
   }
 
   return true;
}

//this function is adapted from my function in crushit assignment
myexit readNcheck_file(const char* fname, char* str)
{
   FILE* filepointer = fopen(fname, "r"); 
   if (filepointer != NULL){
      char temp_string[BIG_NUM] = {'0'};              // optimise this when the function is working
      char temp_content_str[BIG_NUM] = {'0'};
      int fillup_cnt = 0;

      if (fillupNcheck_hawk(filepointer, temp_string, temp_content_str, &fillup_cnt) == checkpoint_fail){
         return graceful_exit;
      }

      if (fillupNcheck_bodyfirst(filepointer, temp_string, temp_content_str, &fillup_cnt) == checkpoint_fail){
         return graceful_exit;
      }

      //writing and checking the rest of the body if it exists

      while (fscanf(filepointer, "%s", temp_string) == 1){
         temp_content_str[fillup_cnt] = '-';
         fillup_cnt++;
         line_fillup(temp_string, temp_content_str, &fillup_cnt);
      }

      strcpy(str, temp_content_str);
      fclose(filepointer); 
   }

   return normal_operation;
}

checkpoint fillupNcheck_bodyfirst(FILE* filepointer, char* temp_string, char* temp_content_str, int* fillup_cnt)
{
   if (fscanf(filepointer, "%s", temp_string) != 1){
      return checkpoint_fail;
   }
   temp_content_str[(*fillup_cnt)] = '-';
   fillup_cnt++;
   line_fillup(temp_string, temp_content_str, fillup_cnt);

   return checkpoint_pass;
}

checkpoint fillupNcheck_hawk(FILE* filepointer, char* temp_string, char* temp_content_str, int* fillup_cnt)
{
   if (fscanf(filepointer, "%s", temp_string) != 1){
      return checkpoint_fail;
   }
   if (hawk_check(temp_string) == checkpoint_fail){
      return checkpoint_fail;
   }
   line_fillup(temp_string, temp_content_str, fillup_cnt);

   return checkpoint_pass;
}

checkpoint hawk_check(char* temp_string)
{
   if (strlen(temp_string) != 1){
      return checkpoint_fail;
   }

   if (only_uprletter(temp_string) == checkpoint_fail){
      return checkpoint_fail;
   }

   return checkpoint_pass;
}

checkpoint body_check(char* temp_string)
{
   if (strlen(temp_string) < 1 || strlen(temp_string) > 6){
      return checkpoint_fail;
   }

   return checkpoint_pass;
}

checkpoint only_uprletter(char* temp_string)
{
   for (int letter = 0; temp_string[letter]; letter++){
      if (temp_string[letter] < 'A' || temp_string[letter] > 'Z'){
         return checkpoint_fail;
      }
   }
   return checkpoint_pass;
}

void line_fillup(char* temp_string, char* temp_content_str, int* fillup_cnt)
{
   for (long unsigned int letter = 0; temp_string[letter]; letter++){
         temp_content_str[(*fillup_cnt)] = temp_string[letter];
         (*fillup_cnt)++;
   }
}

void test(void)
{
   char str[(BRDSZ*BRDSZ+BRDSZ+2)];
   file2str("10moves.brd", str);
   printf("%s\n", str);
   assert(only_uprletter("ABCXYZ") == checkpoint_pass);
   assert(only_uprletter("ABCXYz") == checkpoint_fail);
   assert(only_uprletter("A") == checkpoint_pass);
   assert(only_uprletter("!") == checkpoint_fail);
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