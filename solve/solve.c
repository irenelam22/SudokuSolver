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

// Function prototype
bool solve_puzzle(puzzle_t* puzzle);

/******* solve ********/
/* Main driver method for solve
 * Input:
 * file_name: the pathname of a puzzle-formatted file
 * Output: none (directly prints the puzzle to stdout)
 */
void solve(FILE* puzzle_file) 
{
    if ( puzzle_file == NULL ){
        fprintf(stderr, "Invalid puzzle file passed\n");
        return;
    }

    puzzle_t* puzzle = puzzle_load(puzzle_file);             // create our puzzle
    if (puzzle == NULL) { 
        fclose(puzzle_file);
	    return;
    }

    if (solve_puzzle(puzzle)) {                              // try to solve the puzzle
        puzzle_print(stdout, puzzle);                        // if we solved it... display
    } 
    else {                                                   // otherwise, note that the puzzle solve failed
        printf("Bad input\n");
        puzzle_print(stdout, puzzle);
    }
    
    fclose(puzzle_file);                                     // Clean up memory 
    puzzle_delete(puzzle); 
    return;
}

/******* solve_puzzle ********/
/* Fills in the entire puzzle (main solving method)
 * Inputs: puzzle
 * Output: true if solved, false otherwise
 */
bool solve_puzzle(puzzle_t* puzzle)
{
    if ( puzzle == NULL ){
        fprintf(stderr, "Invalid parameters for solve_puzzle\n");
        return false;
    }
    unit_t* nextUnit = next_unit(puzzle);                           // Retrieve next unit (if any)
    if (nextUnit == NULL) {
        return true;
    }
    unit_t *unit = puzzle[nextUnit -> row_num][nextUnit -> col_num]; // extract the nextUnit from the puzzle
    
  
    delete_unit(nextUnit);               // Delete the created unit, once we have the proper unit in the puzzle 

    int temp = 0;
    possibles_create(puzzle, unit);                     // create the possibles list
    if (possibles_isEmpty(unit)) {                      // if there are no possible values...
        unit -> val = 0;                                // reset the unit's value to zero
        return false;                                   // note that this puzzle is not solved
    }

    while ((temp = possibles_get_one(unit)) != -1){     // while we can extract from our possibles list
        unit -> val = temp;                             // fill this unit's value with this extracted value            
        if (solve_puzzle(puzzle)) {                     // recursively call this function
            return true;                                // if every unit gets filled, then we solved the puzzle
        }
        possibles_remove(unit, temp);
    }
    unit -> val = 0;
    return false;                                       // if not every unit gets filled, we did not solve
}