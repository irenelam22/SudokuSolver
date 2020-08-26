/* 
puzzle.c – implementation for puzzle class
The puzzle initializes a puzzle struct, essentially a 2D array of units
in a 9x9 grid. The following implementations instantiate/maintain/delete this
puzzle. These methods include a creation, iteration, pretty printing, finding
the next available unit, updating the possibles list, and deleting the puzzle.
Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "puzzle.h"
#include "./unit.h"
#include "../libcs50/file.h"
#include "../libcs50/memory.h"

// Constant instantiation
const int MAX_ROW = 9; 
const int MAX_COL = 9; 
const int UNIT_SIZE = 32;  
const int EMPTY_CELL = 0;

/*******puzzle_new********/
/* Create new empty puzzle, where all values are 0
 * Inputs: none
 * Outputs: new puzzle
 */
puzzle_t* puzzle_new()
{
    // Allocate space for entire puzzle 
    puzzle_t* puzzle = assertp(malloc(MAX_ROW*MAX_COL*UNIT_SIZE), "puzzle malloc failed"); 
    int unit_num = 1; 
    for (int i = 0; i < MAX_ROW; i++) {

        // Allocate space for each row 
        puzzle[i] = assertp(malloc(MAX_COL*UNIT_SIZE), "puzzle row malloc failed"); 
        
        // Instantiate a unit for each of the 9x9 spaces within the puzzle
        for (int j = 0; j < MAX_COL; j++) {            
            puzzle[i][j] = unit_new(unit_num, EMPTY_CELL);
            unit_num++; 
        }
    }
    return puzzle; 
}

/*************puzzle_print*************/
/* Printing method
    prints puzzle like so: 
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
* Inputs: 
    - file to print to
    - puzzle to be printed
* Ouputs: none (prints directly to file)
*/
void puzzle_print(FILE *fp, puzzle_t *puzzle)
{
    for (int i = 0; i < MAX_ROW; i++) {
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
    puzzle_t *puzzle = assertp(malloc(MAX_COL*MAX_ROW*UNIT_SIZE), "puzzle load malloc failed"); 
    int row = 0;
    int col = 0; 
    int unit_num = 1; 
    int val; 
    char *line;

    // Go through entire file, line by line 
    while ((line = freadlinep(fp)) != NULL) {
        // Skip empty lines, or lines that start with "-"
        if (strlen(line)==0 || line[0] == 45) {
            free(line); 
            continue;
        }
        // Otherwise, allocate memory for the row and process the line
        puzzle[row] = assertp(malloc(MAX_COL*UNIT_SIZE), "puzzle load malloc failed");
        for (int i = 0; i < strlen(line); i++) {
            // If character is a digit
            if (isdigit(line[i])) {
                // If the next character is also a digit, then the format is invalid
                if (i+1<strlen(line) && isdigit(line[i+1])) {
                    fprintf(stderr, "Invalid puzzle format\n"); 
                    return NULL; 
                }
                // Subtract out 48 to get actual digit value
                val = line[i] - 48;
                // Insert into puzzle, and increment unit_num and column
                puzzle[row][col] = unit_new(unit_num, val); 
                unit_num++; 
                col++; 
            }
            // If character is not a space, or "|", then the format is invalid
            else if (line[i] != 32 && line[i] != 124) {
                fprintf(stderr, "Invalid puzzle format\n"); 
                return NULL; 
            }
        }
        // Free memory, and move to the next row
        free(line);
        row++; 
        col = 0; 
    }
    // If we didn't receive enough units for the puzzle, then the format is invalid
    if (unit_num-1 < MAX_ROW*MAX_COL) {
        fprintf(stderr, "Invalid puzzle format\n"); 
        return NULL;
    }
    // Otherwise, puzzle has a valid format
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

/********* puzzle_iterate ************/
/* Iterate method for the puzzle, calls the provided itemfunc method on each
 * unit of the puzzle
 * Inputs:
 *  - puzzle file to iterate through
 *  - pointer arg
 *  - itemfunc to call on each unit
 * Output: none (dependent on provided itemfunc)
 */
void puzzle_iterate(puzzle_t* puzzle, void *arg, void (*itemfunc)(void *arg, unit_t* cell))
{
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            itemfunc(arg, puzzle[i][j]);
        }
    }
}

/*********puzzle_delete************/
/* Delete the provided puzzle and free necessary memory
 * Input: puzzle to be deleted
 * Output: none
 */
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
    unit_t* unit = ptr;
    if (unit->possibles != NULL) {
        return;
    }
    // Instantiate values of unit pointer
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
 * Inputs: puzzle to find the next unit
 * Output: next available unit
*/
unit_t* next_unit(puzzle_t* puzzle) 
{
    // Instantiate a dummy unit
    unit_t* cell = unit_new(1, 0);

    // Free unused memory
    counters_delete(cell->possibles);
    cell->possibles = NULL;

    // Iterate to find the first valid unit
    puzzle_iterate(puzzle, cell, first_valid_unit);

    // If the cell is empty, delete the allocated memory from above 
    if (cell->possibles == NULL) {
        delete_unit(cell); 
        return NULL;
    }
    return cell;
}


/******* possibles_create ********/
/* Creates a possibles set, based on values in the row/col/box
 * Inputs: puzzle, unit
 * Output: newly created set
*/
counters_t* possibles_create(puzzle_t* puzzle, unit_t* unit) 
{
    // Populate with numbers 1 through 9
    counters_t* set = counters_new();
    for (int i = 1; i < 10; i++) {
        counters_add(set, i);
    }
    unit -> possibles = set;

    // Update the possibles list based on row/col/box values
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
        fprintf(stderr, "processing_helper received NULL input(s)\n");
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

    // Remove from the possibles list if the value appears in the row/col/box
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
