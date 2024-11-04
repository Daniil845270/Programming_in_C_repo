/* Converts file definition of starting board
into a string, to make checking etc. easier.
File contains the hawk tile, then each row
of the board in turn per line.
Returned strings is of the form A-ABC-BCA-BAC, each
row is separated by a '-' symbol and the hawk tile
is specified first.
Args : Name of file to open, str to be filled.
Returns: false if any of the 2 pointers are NULL, if
the file can't be opened, or is badly formed;
else returns true.
*/

// one of the test cases -> check that the created strings in the readNcheck_file won't casue a stack_buffer_overflow

bool file2str(const char* fname, char* str)
{
   what does this function have to do
   1) open a file and transfer its contents into a string


   2) what do I need to check
      pointers to file
         - if ny pointers are null -> false
      string check
         - if the length of the string is less than 200,000 -> return false (use strlen)
      file reading
         - if a file can not be read or doesnt exist - copy&paste the filereading function from crushit and adapt it + check the slides for any additional checks 
      file contents
         //write an assert that checks if I wrote empty hawk and body correctly
         - if any non-uppercase characters -> return false
         - hawk
            - if absent -> return false
            - if more than one characters -> return false
         - body
            - if absent -> return false
            - if column number is not the same in all rows -> return false 
            - if the dimentions exceed 6x6 -> return false

   pseudocode 
   if (file2str_argcheck(fname, str) == checkpoint_fail){return false} -> 
   
         if  (check_pointer(fname, str) == checkpoint_fail){
            return checkpoint_fail
         }

         if (input_strlen(str) == checkpoint_fail){ //it is useless since I define it in the mydefrs/h
            return checkpoint_fail
         }

         if (filereading() == checkpoint_fail){
            return checkpoint_fail
         }

         return checkpoint_pass

   //in main, str is initialised with garbage -> the checkers of the contents of the string may fail to spot a problem
   fill_str_w_null(str, strlen(str))

   // this is jsut going to be a copy of whatever is in the file into the string format with whatever is (or isn't) in the file
   //each new line starts with a dash
      if (copy_file2str(fname, str) == graceful_exit){return false} 
         if (letter_check(str) == checkpoint_fail){return checkpoint_fail} - checks that the string consists only ofuppercase letters and dashes (this 
         function can not be put in the content check because of the special case)

   //

   //if the file is empty, will the transfer even work?

   if (file2str_contentcheck(fname, str) == checkpoint_fail){return false} -> 
      if (dimentions_check(str) == checkpoint_fail){return checkpoint_fail} - hawk_check(str) + 
         if (hawk_check(str) == checkpoint_fail){return checkpoint_fail} - if the first item must be an uppercase letter and second a dash (only one letter check)
         if (body_check(str) == checkpoint_fail){return checkpoint_fail} - checks that the number of colums is the same in each row, 
         that the number of columns does not exceed 6 and the number of rows does not exceed 6. There must be at least one row and at least one column


}

int solve(state* s, bool verbose)
{
   solv mysolution = find_solution(s);

   if (verbose == true){
      print_ancestry(state* s);
   }
   
   return 
}

solv find_solution(state* s)
{
   while (s->solved == false){
      for (int col = 0; col < s->clmn; col++){
         create_dauthers(s->brdlist[dcnt].str);
         if (find_match(s->brdlist[dcnt].str) == false){
            if (is_solution(s->brdlist[dcnt].str) == true){
               // s->solved = true;
               return solution_found;
            }
            dcnt++;
         }
         else{
            if ((dcnt == pcnt + 1) && (col == s->clmn - 1)){
               return solution_doesnt_exist;
            }
         }
      }
      pcnt++;
   }
}