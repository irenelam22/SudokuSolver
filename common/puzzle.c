/* 

file: puzzle.c – implementation for puzzle class
assignment: final project – sudoku
group: project-kidd

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "puzzle.h"
#include "./unit.h"
#include "../libcs50/file.h"
#include "../libcs50/memory.h"

// TODO: Should have some way for puzzle to designate non-changeable units (Irene)


const int MAX_ROW = 9; 
const int MAX_COL = 9; 
const int UNIT_SIZE = 32;  // Note: sizeof(unit_t) wasn't working, so I hard-coded it as a global variable
const int EMPTY_CELL = 0;

/*******puzzle_new********/
/* Create new empty puzzle, where all values are 0
*/
puzzle_t* puzzle_new()
{
    // Allocate space for entire puzzle 
    puzzle_t* puzzle = assertp(malloc(MAX_ROW*MAX_COL*UNIT_SIZE), "puzzle malloc failed"); 
    int unit_num = 1; 
    for (int i = 0; i < MAX_ROW; i++) {

        // Allocate space for each row 
        puzzle[i] = assertp(malloc(MAX_COL*UNIT_SIZE), "puzzle row malloc failed"); 
        
        for (int j = 0; j < MAX_COL; j++) {
            /* note: it would be easy to initialize each 
               unit with a given row, col number --> don't 
               need all the math / extra work in unit_new */
            
            puzzle[i][j] = unit_new(unit_num, EMPTY_CELL);
            unit_num++; 
        }
    }
    return puzzle; 
}

/*************puzzle_print*************/
/* prints puzzle like so: 
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    ---------------------
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    ---------------------
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
*/
void puzzle_print(FILE *fp, puzzle_t *puzzle)
{
    for (int i = 0; i < MAX_ROW; i++) {
        /* note: if we want different size sudokus, 
           we'll have to fix these hard-coded numbers 
        */
        if (i == 3 || i == 6) {
            fprintf(fp, "---------------------\n"); 
        }
        for (int j = 0; j < MAX_COL; j++) {
            if (j == 3 || j == 6) {fprintf(fp, "| "); }
            fprintf(fp, "%d ", get_unit_val(puzzle[i][j])); 
        }
        fprintf(fp, "\n");
    }
}

/**********puzzle_load*************/
/* Takes a pointer to a file that contains a properly formatted
*  sudoku, then loads that sudoku into a new puzzle struct, 
*  with the proper values for each unit
*/
puzzle_t *puzzle_load(FILE *fp)
{
    // Initialize new puzzle 
    puzzle_t *puzzle = malloc(MAX_COL*MAX_ROW*UNIT_SIZE); 
    int row = 0;
    int col = 0; 
    int unit_num = 1; 
    int val; 
    // Go through entire puzzle 
    while (unit_num <= MAX_COL*MAX_ROW) {
        // Load in the numbers from the file 
        while (fscanf(fp, "%d", &val) == 1) {
            // When we finish a row, increment row count, reset column count, 
            // and allocate memory for the new row 
            if (unit_num % MAX_COL == 1) {
                if (unit_num > 1) {row++;}
                col = 0; 
                puzzle[row] = malloc(MAX_COL*UNIT_SIZE); 
            }
            // Initialize new unit at the proper unit_num, row, and col
            puzzle[row][col] = unit_new(unit_num, val); 
            unit_num++; 
            col++; 
        }
        // Skip "|" in file 
        fscanf(fp, "|"); 
    }
    return puzzle; 
}

/**********puzzle_get_unit*************/
/* Returns the unit of a puzzle given its row and col number
 * Inputs: puzzle, row number, col number of desired unit
 * Output: unit
*/
unit_t* puzzle_get_unit(puzzle_t* puzzle, int row, int col)
{
    if (puzzle == NULL) {
        fprintf(stderr, "puzzle_get_unit received a NULL puzzle");
        return NULL;
    }
    if (row < 0 || row > 8) {
        fprintf(stderr, "puzzle_get_unit received an out of bounds row");
        return NULL;
    }
    if (col < 0 || col > 8 ) {
        fprintf(stderr, "puzzle_get_unit received an out of bounds col");
        return NULL;
    }
    return puzzle[row][col];
}

void puzzle_iterate(puzzle_t* puzzle, void *arg, void (*itemfunc)(void *arg, unit_t* cell))
{
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            itemfunc(arg, puzzle[i][j]);
        }
    }
}

/*********puzzle_delete************/
void puzzle_delete(puzzle_t *puzzle)
{
    // Delete all units
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            delete_unit(puzzle[i][j]); 
        }
        // Free allocated space for rows 
        free(puzzle[i]);
    }
    // Finally, free the puzzle itself
    free(puzzle); 
}


/*******first_valid_unit********/
/* Finds the first unit within a puzzle not yet filled in
 * itemfunc method to be called in puzzle_iterate
 * Inputs: pointer, current cell
 * Output: none (directly populates ptr)
*/
void first_valid_unit(void* ptr, unit_t* current_cell) 
{
    // EMPTY_CELL = 0;
    unit_t* unit = ptr;
    if (unit->possibles != NULL) {
        return;
    }
    if (current_cell -> val == 0) {
        unit -> val = current_cell -> val;
        unit -> unit_num = current_cell -> unit_num;
        unit -> row_num = current_cell -> row_num;
        unit -> col_num = current_cell -> col_num;
        unit -> box_num = current_cell -> box_num;
        unit -> possibles = current_cell -> possibles;
    }
}

/*******next_unit********/
/* Finds the first unit within a puzzle not yet filled in
 * Inputs: puzzle
 * Output: unit
*/
unit_t* next_unit(puzzle_t* puzzle) 
{
    unit_t* cell = unit_new(1, 0);
    counters_delete(cell->possibles);
    cell->possibles = NULL;
    puzzle_iterate(puzzle, cell, first_valid_unit);
    if (cell->possibles == NULL) {
        // printf("cell is empty\n");
        // If the cell is empty, delete the allocated memory from above 
        delete_unit(cell); 
        return NULL;
    }
    
    // printf("next_unit(%d, %d) -- ", cell -> row_num, cell -> col_num);
    return cell;
}


/******* possibles_create ********/
/* Creates a possibles set, based on values in the row/col/box
 * Inputs: puzzle, unit
 * Output: newly created set
*/
counters_t* possibles_create(puzzle_t* puzzle, unit_t* unit) 
{
    counters_t* set = counters_new();
    for (int i = 1; i < 10; i++) {
        counters_add(set, i);
    }
    unit -> possibles = set;
    updating_possibles(puzzle, unit);
    return set;
}

/******* updating_possibles ********/
/* Updates the list of possible numbers by traversing through puzzle
 * and removing values that appear in the row, column, and box
 * Inputs: puzzle, unit
 * Output: none
*/
void updating_possibles(puzzle_t* puzzle, unit_t* unit)
{
    puzzle_iterate(puzzle, unit, updating_possibles_helper);
}

/******* updating_possibles_helper ********/
/* Updates the list of possible numbers by traversing through puzzle
 * and removing values that appear in the row, column, and box
 * itemfunc method for updating_possibles
 * Inputs: arg (unit -- to be modified), unit (that is compared)
 * Output: none
*/
void updating_possibles_helper(void *arg, unit_t* unit) 
{
    if (arg == NULL || unit == NULL) {
        fprintf(stderr, "processing_helper received NULL input(s)");
        return;
    }
    unit_t* curr_unit = arg;
    // Values of unit we're comparing with
    int curr_row = curr_unit -> row_num;
    int curr_col = curr_unit -> col_num;
    int curr_box = curr_unit -> box_num;

    // Values of units within puzzle we're trying to update
    int temp_row = unit -> row_num;
    int temp_col = unit -> col_num;
    int temp_box = unit -> box_num;
    if (curr_row == temp_row || curr_col == temp_col || curr_box == temp_box) {
        possibles_remove(curr_unit, unit -> val);
    }
}

/******* solveable_helper ********/
/* Checks whether a puzzle is solveable (e.g. all units have a possible value)
 * itemfunc for is_puzzle_solveable
 * Inputs: pointer (boolean), unit
 * Output: none
*/
void solveable_helper(void* ptr, unit_t* current_cell)
{
    bool* context = ptr;
    if (possibles_isEmpty(current_cell)) {
        *context = false;
    }
}

/******* is_puzzle_solveable ********/
/* Checks whether a puzzle is solveable (e.g. all units have a possible value)
 * Inputs: puzzle
 * Output: true if solveable, false otherwise
*/
bool is_puzzle_solveable(puzzle_t* puzzle) 
{
    bool solveable = true;
    puzzle_iterate(puzzle, &solveable, solveable_helper);
    return solveable;
}