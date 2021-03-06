#include <stdio.h>
#include <stdlib.h>
#include "../common/unit.h"
#include "../common/puzzle.h"

#ifndef __CREATE_H
#define __CREATE_H

/******* create *******/
/* Main creating functionality 
 *   Inputs:
 *     filename of where to print the puzzle 
 *     indicator (1 if printing to stdout, 0 if printing to file)
 *   Output: 
 *    printed puzzle, to either stdout or given filename
 */
void create(FILE *fp, int minshown);

/******* fill_puzzle *******/
/* Randomly fills in the entire puzzle, making sure sudoku rules are held 
 *   Input: puzzle struct 
 *   Output: true if puzzle filled properly, false otherwise 
 */
bool fill_puzzle(puzzle_t *puzzle);

/******* hide_nums *******/
/* Randomly selects units to remove from the given puzzle 
 *   Inputs: 
 *      * puzzle: current puzzle struct 
 *      * fullpuzz: the solved full version of puzzle, as generated 
 *                  by fill_puzzle
 *      * minshown: the minimum amount of numbers to be shown
 *  Output: 
 *      * true if enough numbers are hidden (at least 40), false otherwise 
 */
bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz, int minshown);

/******* remove_random_num *******/
/* Randomly removes one unit from a given puzzle
 * Inputs: 
 * 	* puzzle: current puzzle struct to remove from
 * 	* numshown: pointer to the current number of units shown in the puzzle
 * 	* row, col: pointers to where we are removing from in the puzzle
 * Output: 
 * 	* value of the unit removed from the puzzle, in case it needs to get added back  
 */
int remove_random_num(puzzle_t *puzzle, int *numshown, int* row, int* col);

/******* has_one_solution *******/
/* Our best estimate of testing to see if a puzzle has one unique solution
 *   
 *   Given both an unsolved puzzle and its solution, it calls fill_puzzle 
 *   on the unsolved puzzle to generate a random solution, then compares
 *   the two puzzles to see if the random solution matches the given solution
 *  
 *  Inputs: 
 *       * puzzle: current puzzle struct 
 *       * fullpuzz: solution of current puzzle struct, as generated by 
 *                   fill_puzzle
 *  Output: 
 *       * true if the puzzles match, false otherwise 
 */
bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz);

/******* copy_puzzle *******/
/* Helper function for puzzle_iterate that copies all data values for one 
 *   puzzle into another
 */
void copy_puzzle(void *arg, unit_t* unit);

#endif // __CREATE_H 
