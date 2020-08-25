/*
solve.c -- implementation file for solver

Please see solve.h for more details 

Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../common/puzzle.h"
#include "../common/unit.h"
#include "../libcs50/file.h"
#include "../libcs50/memory.h"
#include "../libcs50/counters.h"
 
bool solve_puzzle(puzzle_t* puzzle);
unit_t* backtrace(puzzle_t* puzzle, unit_t* unit);

void solve(char* file_name)
{
    if ( file_name == NULL ){
        fprintf(stderr, "Please provide a puzzle file to solve\n");
        return;
    }

    FILE* puzzle_file = fopen(file_name, "r");
    if ( puzzle_file == NULL ){
        fprintf(stderr, "Invalid puzzle file passed\n");
        return;
    }
    // Error-handling
    // if (argc < 2) {
    //     fprintf(stderr, "Insufficient number of arguments\n");
    //     return 1;
    // }
    // if (argc > 2) {
    //     fprintf(stderr, "Too many arguments provided\n");
    //     return 1;
    // }

    // // Attempt to open file
    // FILE* puzzle_file = fopen(argv[1], "r");
    // if (puzzle_file == NULL) {
    //     fprintf(stderr, "Invalid puzzle file passed\n");
    //     return 1;
    // }

    puzzle_t* puzzle = puzzle_load(puzzle_file); 

    if (solve_puzzle(puzzle)) {
        puzzle_print(stdout, puzzle);
    } else {
        printf("Puzzle Solve Failed\n");
        puzzle_print(stdout, puzzle);
    }
    
    // Clean up memory 
    fclose(puzzle_file);
    puzzle_delete(puzzle); 
    return;
}

/*******solve_puzzle********/
/* Fills in the entire puzzle (main solving method)
 * Inputs: puzzle
 * Output: true if solved, false otherwise
 */
bool solve_puzzle(puzzle_t* puzzle)
{
    // Retrieve next unit (if any)
    unit_t* nextUnit = next_unit(puzzle);
    if (nextUnit == NULL) {
        return true;
    }
    unit_t *unit = puzzle[nextUnit -> row_num][nextUnit -> col_num];
    
    // Delete the created unit, once we have the proper unit in the puzzle 
    delete_unit(nextUnit); 

    int temp = 0;
    possibles_create(puzzle, unit);
    if (possibles_isEmpty(unit)) {
        unit -> val = 0;
        return false;
    }

    while ((temp = possibles_get_one(unit)) != -1){
        unit ->val = temp;
        if (solve_puzzle(puzzle)) {
            return true;
        }
        possibles_remove(unit, temp);
    }
    unit -> val = 0;
    return false;
}

/*******backtrace********/
/* Cleans up current unit and returns the previous unit
 * Inputs: puzzle, unit
 * Output: previous unit (if any)
*/
unit_t* backtrace(puzzle_t* puzzle, unit_t* unit)
{
    counters_t* possibles = unit -> possibles;
    counters_delete(possibles);
    unit -> val = 0;
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
        printf("Clearing unit num: %d\n", new_unit->unit_num);
        possibles_remove(new_unit, val);
        return new_unit;
    }
    return NULL;
}