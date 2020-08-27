/*
solve.h -- header file for solver

Solve takes in a (presumably) unsolved puzzle and recursively backtraces
to populate each unit in the puzzle. In particular, each unit maintains a 
set of possible values (of which discludes values from the unit's row, column,
and block). While this set is populated, the program attempts to 
insert one of these values into the puzzle, and backtraces to a previous unit 
if no such possible values exist. Solve continues this process until the entire
puzzle is populated.

Please see the IMPLEMENTATION.md for more details.

Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include "../common/unit.h"
#include "../common/puzzle.h"

#ifndef SOLVE_H
#define SOLVE_H

/**************** functions ****************/
/**************** solve ****************/
/* Given a puzzle, return a solved puzzle (according to the rules of sudoku)
 * 
 * Caller provides:
 *   a file name
 * We return:
 *   nothing
 * We do:
 *  ignore if file name is NULL or is not a readable file
 *  load in the puzzle
 *  try to solve the puzzle and print the resulting puzzle
 *  clean up
 */
void solve(FILE* file_name);

/**************** solve_puzzle ****************/
/* Recursive function to solve a puzzle
 * 
 * Caller provides:
 *   a puzzle
 * We return:
 *   true if puzzle was solved
 *   false if puzzle was not solved
 * We do:
 *  ignore if NULL puzzle passed in
 *  while we can get the next unit
 *  try to fill that unit
 *  backtrace and revise if necessary
 */
bool solve_puzzle(puzzle_t* puzzle);

#endif
