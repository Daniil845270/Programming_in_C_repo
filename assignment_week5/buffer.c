void horisontally_matching_tilesfinder(state* s, state* matches_snapshot)
{
    for (int row = 0; row < matches_snapshot->rows && row < s->rows; row++){
        for (int column = 1; column < (WIDTH - 1); column++){
            if (horisontal_comparison(s, row, column, 1) == true && horisontal_comparison(s, row, column, -1) == true){
                matches_snapshot->board[row][column - 1] = REPLACE_TILE;
                matches_snapshot->board[row][column] = REPLACE_TILE;
                matches_snapshot->board[row][column + 1] = REPLACE_TILE;
            }
        }
    }
}

void vertically_matching_tilesfinder(state* s, state* matches_snapshot)
{
    for (int row = 1; row < matches_snapshot->rows - 1 && row < s->rows - 1; row++){
        for (int column = 0; column < WIDTH; column++){
            if (vertical_comparison(s, row, column, 1) == true && vertical_comparison(s, row, column, -1) == true){
                matches_snapshot->board[row - 1][column] = REPLACE_TILE;
                matches_snapshot->board[row][column] = REPLACE_TILE;
                matches_snapshot->board[row + 1][column] = REPLACE_TILE;
            }
        }
    }
}

bool horisontal_comparison(state* s, int row, int column, int direction)
{
    int adj_row;
    if (s->is_board_full == true){
        adj_row = s->rows - HEIGHT + row;
        if ((s->board[(adj_row)][column] != NO_TILE)){
            if ((s->board[(adj_row)][column] == s->board[(adj_row)][column + direction])){
                return true;
            }
        }
        return false;
    }
    else{
        if ((s->board[row][column] != NO_TILE)){
            if ((s->board[row][column] == s->board[row][column + direction])){
                return true;
            }
        }
        return false;
    }
    return false;
}

bool vertical_comparison(state* s, int row, int column, int direction)
{
    if (s->is_board_full == true){
        int adj_row = s->rows - HEIGHT + row;
        if (s->board[adj_row][column] != NO_TILE){
            if ((s->board[adj_row][column] == s->board[(adj_row + direction)][column])){
                return true;
            }
        }
        return false;
    }
    else{
        if (s->board[row][column] != NO_TILE){
            if ((s->board[row][column] == s->board[row + direction][column])){
                return true;
            }
        }
        return false;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void horisontally_matching_tilesfinder(state* s, state* matches_snapshot)
{
    for (int row = 0; row < matches_snapshot->rows && row < s->rows; row++){
        for (int column = 1; column < (WIDTH - 1); column++){
            if (twotile_comparison(s, row, column, 0, 1) == true && twotile_comparison(s, row, column, 0, -1) == true){
                matches_snapshot->board[row][column - 1] = REPLACE_TILE;
                matches_snapshot->board[row][column] = REPLACE_TILE;
                matches_snapshot->board[row][column + 1] = REPLACE_TILE;
            }
        }
    }
}

void vertically_matching_tilesfinder(state* s, state* matches_snapshot)
{
    for (int row = 1; row < matches_snapshot->rows - 1 && row < s->rows - 1; row++){
        for (int column = 0; column < WIDTH; column++){
            if (twotile_comparison(s, row, column, 1, 0) == true && twotile_comparison(s, row, column, -1, 0) == true){
                matches_snapshot->board[row - 1][column] = REPLACE_TILE;
                matches_snapshot->board[row][column] = REPLACE_TILE;
                matches_snapshot->board[row + 1][column] = REPLACE_TILE;
            }
        }
    }
}

bool twotile_comparison(state* s, int row, int column, int direction_UD, int direction_LR)
{
    if (s->is_board_full == true){
        int adj_row = s->rows - HEIGHT + row;
        if (s->board[adj_row][column] != NO_TILE){
            if (s->board[adj_row][column] == s->board[(adj_row + direction_UD)][(column + direction_LR)]){
                return true;
            }
        }
        return false; 
    }
    else{
        if (s->board[row][column] != NO_TILE){
            if (s->board[row][column] == s->board[(row + direction_UD)][(column + direction_LR)]){
                return true;
            }
        }
        return false;
    }
    return false;
}