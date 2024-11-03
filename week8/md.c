#include "mydefs.h"

bool file2str(const char* fname, char* str)
{
   if (fname == NULL || str == NULL){
      return false;
   }

   // char filename_or_string[MAXSTR] = {'0'}; //don't need it
   if (readNcheck_file(fname, str) != normal_operation){
      return false;
   }

   return true;
}

myexit readNcheck_file(const char* fname, char* str)
{
   FILE* filepointer = fopen(fname, "r"); 
   if (filepointer != NULL){
      char temp_string[BIG_NUM] = {'0'};              // optimise this when the function is working
      char temp_content_str[BIG_NUM] = {'0'};
      int fillup_cnt = 0;
      while (fscanf(filepointer, "%s", temp_string) == 1){
         for (long unsigned int letter = 0; temp_string[letter]; letter++){
               temp_content_str[fillup_cnt] = temp_string[letter];
               fillup_cnt++;
         }
      }
      strcpy(str, temp_content_str);
      fclose(filepointer); 
   }

   return normal_operation;
}

void test(void)
{
   char str[(BRDSZ*BRDSZ+BRDSZ+2)];
   file2str("10moves.brd", str);
   printf("%s\n", str);
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