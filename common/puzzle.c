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

const int MAX_ROW = 9; 
const int MAX_COL = 9; 
// sizeof(unit_t) wasn't working, so I hard-coded it as a global variable
const int UNIT_SIZE = 32; 

typedef unit_t **puzzle_t; 

/*******puzzle_new********/
/* Create new empty puzzle, where all values are 0
*/
puzzle_t* puzzle_new()
{
    // Allocate space for entire puzzle 
    puzzle_t* puzzle = malloc(MAX_ROW*MAX_COL*UNIT_SIZE); 
    int unit_num = 1; 
    for (int i = 0; i < MAX_ROW; i++) {

        // Allocate space for each row 
        puzzle[i] = malloc(MAX_COL*UNIT_SIZE); 
        
        for (int j = 0; j < MAX_COL; j++) {
            /* note: it would be easy to initialize each 
               unit with a given row, col number --> don't 
               need all the math / extra work in unit_new */
            
            puzzle[i][j] = unit_new(unit_num, 0);
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
void puzzle_print(puzzle_t *puzzle)
{
    for (int i = 0; i < MAX_ROW; i++) {
        /* note: if we want different size sudokus, 
           we'll have to fix these hard-coded numbers 
        */
        if (i == 3 || i == 6) {
            printf("---------------------\n"); 
        }
        for (int j = 0; j < MAX_COL; j++) {
            if (j == 3 || j == 6) {printf("| "); }
            printf("%d ", get_unit_val(puzzle[i][j])); 
        }
        printf("\n");
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