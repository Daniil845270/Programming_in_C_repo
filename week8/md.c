#include "mydefs.h"

bool file2str(const char* fname, char* str)
{
   if (file2str_argcheck(fname, str) == checkpoint_fail){
      return false;
   }
}

checkpoint file2str_argcheck(const char* fname, char* str)
{
   if (fname == NULL || str == NULL){
      return checkpoint_fail;
   }
   if (filereading() == checkpoint_fail){
      return checkpoint_fail
   }
   return checkpoint_pass
}

//this function takes the input pointers and checks if they are null
checkpoint check_pointer(const char* fname, char* str)
{
   if (fname == NULL || str == NULL){
      return checkpoint_fail;
   }
   return checkpoint_pass;
}

//this function checks that the filename exists and cna be successfully read
checkpoint filereading(const char* fname)
{

}






state* str2state(const char* str)
{

   // can actually copy some of the checks from file2str

   // alloc space for state
   // ...
   // Put contents of string into
   // first board of list in state.
   // ...
   // return state;
}

int solve(state* s, bool verbose)
{
}

void test(void)
{
}

/* Many of other functions, as required */