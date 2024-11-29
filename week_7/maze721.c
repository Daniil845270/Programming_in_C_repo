#include "headerfile.h"

//-fsanitize=address

enum step_rec{up, down, left, right};
typedef enum step_rec step_rec;

typedef struct Maze_itr {
    char maze_state[21][21];
    int row;
    int column;
    step_rec prev_step;
    struct Maze_itr* next;
} Maze_itr;

void mv_maze_from_file(char* filename, char maze[21][21]);
void two_d_arr_printer(char arr[21][21]);
int find_entrance(char (*arr)[21]);
void initialise_structures(Maze_itr* step_now, char (*arr)[21], int start_row);
void copy_twod_array(Maze_itr* step_now, char (*arr)[21]);

int main(int argc, char* argv[])
// The sizes of the maze are given on the first line of the file (width,height)
{
    Maze_itr step_now;
    if (argc != 2){
        return 0;
    }
    char maze[21][21] = {{'\0'}}; // probably 
    mv_maze_from_file(argv[1], maze);
    // two_d_arr_printer(maze);
    int start_row = find_entrance(maze);
    // two_d_arr_printer(maze);
    if (start_row == -1){
        return 1;
    }
    // printf("%d\n", start_row);
    initialise_structures(&step_now, maze, start_row);
    two_d_arr_printer(step_now.maze_state);
    two_d_arr_printer(maze);

    return 0;
}

void initialise_structures(Maze_itr* step_now, char (*arr)[21], int start_row)
{
    copy_twod_array(step_now, arr);
    step_now->row = start_row;
    step_now->column = 1;
    step_now->prev_step = left;
    // two_d_arr_printer(step_now->maze_state);
    // printf("%d , %d\n", step_now->column, step_now->column);
}

void copy_twod_array(Maze_itr* step_now, char (*arr)[21])
{
    for (int row = 0; (row < 21) & (arr[row][0] != '\0'); row++){
        for (int column = 0; (column < 21) & (arr[row][column] != '\0'); column++){
            step_now->maze_state[row][column] = arr[row][column];
        }
    }
}

int find_entrance(char (*arr)[21]) // it is assumed that the top and bottom (if there are 20 rows) rows are borders and hense do not contain an entrance
{
    // printf("was here\n");
    for (int row = 1; (row < 19) & (arr[row][0] != '\0'); row++){
        // printf("%c\n", arr[row][0]);
        if (arr[row][0] == ' '){
            arr[row][0] = '.';
            return row;
        }
    }
    return -1;
}

void mv_maze_from_file(char* filename, char maze[][21]) //function not tested
//ideas - 
// 1) check there are at least 2 rows and 2 columns (or more complicated combination)
// 2) check there are no other symbols 
{
    FILE* filepointer = fopen(filename, "r"); 
    char temp_string[21] = {'\0'}; int fillup_cnt = 0;
    if (filepointer != NULL){
        while (fgets(temp_string, 21, filepointer) != NULL){
            strcpy(maze[fillup_cnt], temp_string);
            // printf("%s\n", temp_string);
            fillup_cnt++;
        }
    }
    fclose(filepointer);
}

void two_d_arr_printer(char arr[][21])
{
    for (int row = 0; (row < 21) & (arr[row][0] != '\0'); row++){
        for (int column = 0; (column < 21) & (arr[row][column] != '\0'); column++){
            printf("%c", arr[row][column]);
        }
    }
    printf("\n");
}
