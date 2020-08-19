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
const int MAX_ROW = 9; 
const int MAX_COL = 9; 

void solve_puzzle(puzzle_t* puzzle)
{

    // for each cell
        // if the possibles list is NULL, create the possibles list
        // if the possibles list is empty, backtrace
            // set possibles list to NULL, clean up
            // go back one and remove from possibles list
            // rinse and repeat
}

unit_t* backtrace(puzzle_t* puzzle, unit_t* unit)
{
    counters_t* possibles = unit -> possibles;
    counters_delete(possibles);
    unit_t* new_unit = NULL;
    
    int row = unit -> row_num;
    int col = unit -> col_num;
    int val = unit -> val;

    // NOTE: Should have some way for puzzle to designate non-changeable units
    if (col == 0) {
        col = 8;
        row--;
    }
    else {
        col--;
    }
    if (row >= 0 && col >= 0) {
        new_unit = puzzle_get_unit(puzzle, row, col);
        counters_t* new_possibles = new_unit -> possibles;
        possibles_remove(new_unit, val);
        return new_unit;
    }
    return NULL;
}

void updating_possibles(puzzle_t* puzzle, unit_t* unit)
{
    puzzle_iterate(puzzle, unit, updating_possibles_helper);
}

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
        possibles_remove(unit, curr_unit -> val);
    }
}

void solveable_helper(void* ptr, unit_t* current_cell)
{
    bool* context = ptr;
    if (possibles_isEmpty(current_cell)) {
        *context = false;
    }
}


bool is_puzzle_solveable(puzzle_t* puzzle) 
{
    bool solveable = true;
    puzzle_iterate(puzzle, &solveable, solveable_helper);
    return solveable;
}

/*******first_valid_unit********/
/* Finds the first unit within a puzzle not yet filled in
 * To be called in puzzle_iterate
 * Inputs: pointer, current cell
 * Output: none (directly populates ptr)
*/
void first_valid_unit(void* ptr, unit_t* current_cell) 
{
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
