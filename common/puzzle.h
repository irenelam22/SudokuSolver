/* 
puzzle.h – header file for puzzle class

The puzzle initializes a puzzle struct, essentially a 2D array of units
in a 9x9 grid. The following implementations instantiate/maintain/delete this
puzzle. These methods include a creation, iteration, pretty printing, finding
the next available unit, updating the possibles list, and deleting the puzzle.

Please seee IMPLEMENTATION.md for more details

Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include "unit.h"

#ifndef __PUZZLE_H
#define __PUZZLE_H

// puzzle struct (essentially a 2D array of units)
typedef unit_t **puzzle_t; 

/*******puzzle_new********/
/* Create new empty puzzle, where all values are 0
 * Inputs: none
 * Outputs: new puzzle
 */
puzzle_t* puzzle_new();  

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
void puzzle_print(FILE *fp, puzzle_t *puzzle); 

/**********puzzle_load*************/
/* Takes a pointer to a file that contains a properly formatted
*  sudoku, then loads that sudoku into a new puzzle struct, 
*  with the proper values for each unit
*/
puzzle_t *puzzle_load(FILE *fp); 

/*********puzzle_delete************/
/* Delete the provided puzzle and free necessary memory
 * Input: puzzle to be deleted
 * Output: none
 */
void puzzle_delete(puzzle_t *puzzle); 

/********* puzzle_iterate ************/
/* Iterate method for the puzzle, calls the provided itemfunc method on each
 * unit of the puzzle
 * Inputs:
 *  - puzzle file to iterate through
 *  - pointer arg
 *  - itemfunc to call on each unit
 * Output: none (dependent on provided itemfunc)
 */
void puzzle_iterate(puzzle_t* puzzle, void *arg, void (*itemfunc)(void *arg, unit_t* cell));

/**********puzzle_get_unit*************/
/* Returns the unit of a puzzle given its row and col number
 * Inputs: puzzle, row number, col number of desired unit
 * Output: unit
*/
unit_t* puzzle_get_unit(puzzle_t* puzzle, int row, int col);

/*******first_valid_unit********/
/* Finds the first unit within a puzzle not yet filled in
 * itemfunc method to be called in puzzle_iterate
 * Inputs: pointer, current cell
 * Output: none (directly populates ptr)
*/
void first_valid_unit(void* ptr, unit_t* current_cell); 

/*******next_unit********/
/* Finds the first unit within a puzzle not yet filled in
 * Inputs: puzzle to find the next unit
 * Output: next available unit
*/
unit_t* next_unit(puzzle_t* puzzle); 

/******* possibles_create ********/
/* Creates a possibles set, based on values in the row/col/box
 * Inputs: puzzle, unit
 * Output: newly created set
*/
counters_t* possibles_create(puzzle_t* puzzle, unit_t* unit); 

/******* updating_possibles ********/
/* Updates the list of possible numbers by traversing through puzzle
 * and removing values that appear in the row, column, and box
 * Inputs: puzzle, unit
 * Output: none
*/
void updating_possibles(puzzle_t* puzzle, unit_t* unit); 

/******* updating_possibles_helper ********/
/* Updates the list of possible numbers by traversing through puzzle
 * and removing values that appear in the row, column, and box
 * itemfunc method for updating_possibles
 * Inputs: arg (unit -- to be modified), unit (that is compared)
 * Output: none
*/
void updating_possibles_helper(void *arg, unit_t* unit); 

/******* solveable_helper ********/
/* Checks whether a puzzle is solveable (e.g. all units have a possible value)
 * itemfunc for is_puzzle_solveable
 * Inputs: pointer (boolean), unit
 * Output: none
*/
void solveable_helper(void* ptr, unit_t* current_cell); 

/******* is_puzzle_solveable ********/
/* Checks whether a puzzle is solveable (e.g. all units have a possible value)
 * Inputs: puzzle
 * Output: true if solveable, false otherwise
 */
bool is_puzzle_solveable(puzzle_t* puzzle); 

#endif // __PUZZLE_H 
