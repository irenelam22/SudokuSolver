/*
solve.c -- implementation file for solver

Please see solve.h for more details 

Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include "../common/puzzle.h"
#include "../common/unit.h"

const int EMPTY_CELL = 0;

void solve_puzzle(puzzle_t* puzzle)
{
    
}

/*******first_valid_unit********/
/* Finds the first unit within a puzzle not yet filled in
 * To be called in puzzle_iterate
 * Inputs: pointer, current cell
 * Output: none (directly populates ptr)
*/
void first_valid_unit(void* ptr, unit_t* current_cell) {
    if (ptr != NULL && (current_cell -> val == EMPTY_CELL)) {
        ptr = current_cell;
    }
}

/* (Good to have): prune technique, traverse the puzzle for 
    unit with smallest possibles list */

unit_t* choose_unit(puzzle_t* puzzle) 
{
    unit_t* cell = NULL;
    puzzle_iterate(puzzle, &cell, first_valid_unit);
    if (cell == NULL) {
        return NULL;
    }
    else {
        printf("(%d, %d)", cell -> row_num, cell -> col_num);
        return cell;
    }
}
