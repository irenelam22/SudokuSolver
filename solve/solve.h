/*
solve.c -- header file for solver

Solve takes in a (presumably) unsolved puzzle and uses the backtrace method
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

void solve(char* file_name);
void solve_puzzle(puzzle_t* puzzle);
unit_t* backtrace(puzzle_t* puzzle, unit_t* unit);

#endif
