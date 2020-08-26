/*

File: create.c
Description: In this file, we have a main "create" function, and a few helper 
functions. Effectively, the create program will be called by our sudoku program 
to create a new sudoku puzzle. The user will have the option either to provide
a file to which the output will be sent, or to provide no file name (the output 
will be sent to stdout)

Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include "../solve/solve.h"
#include "../common/puzzle.h"
#include "../common/unit.h"

// local function prototypes
static bool fill_puzzle(puzzle_t *puzzle); 
static bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz, int minshown); 
static bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz); 
static void copy_puzzle(void *arg, unit_t* unit); 

/******* create *******/
/* Main creating functionality 
 * *  Inputs:
 * *	filename of where to print the puzzle 
 * *	indicator (1 if printing to stdout, 0 if printing to file)
 * *  Output: 
 * *   printed puzzle, to either stdout or given filename
 * */
void create(char* file_name, int indicator)
{
    if ( indicator < 0 || indicator > 1){           // check arguments; note: file_name may be NULL if we're printing to stdout
        fprintf(stderr, "Error with indicator\n");
        return;
    }
    FILE* fp;
    char* file_name_copy;               
    if ( indicator == 1){        // if our indicator equals one, then no file was provided (print to stdout)
        fp = stdout;
    }
    else{                                                   // otherwise, there should be a provided file
        file_name_copy = malloc(strlen(file_name) + 1);     // allocate memory for a copy of the file name
        if ( file_name_copy == NULL ){                      // make sure the memory was allocated properly
            fprintf(stderr, "Failed to allocate memory for file.\n");
            return;
        }
        strcpy(file_name_copy, file_name);                  // copy the name into the new allocated memory
        if ( (fp = fopen(file_name_copy, "w")) == NULL) {   // try to open the file for writing; exit if error
            fprintf(stderr, "%s is not a writeable file\n", file_name_copy); 
            free(file_name_copy); 
            return; 
        }

    }

    puzzle_t *puzzle = puzzle_new();                     // Create empty puzzle and randomly fill in all the values 
    fill_puzzle(puzzle); 

    puzzle_t *fullpuzz = puzzle_new();                   // Store the completed puzzle for later
    puzzle_iterate(puzzle, fullpuzz, copy_puzzle); 

    while (!hide_nums(puzzle, fullpuzz, 20)) {           // Keep removing numbers while there's still only one solution
        puzzle_iterate(fullpuzz, puzzle, copy_puzzle);   // and while we have <= 41 showing numbers
    }

    puzzle_print(fp, puzzle);                            // Print finished puzzle to provided file (or stdout)

    puzzle_delete(puzzle);                               // Clean everything up from memory 
    puzzle_delete(fullpuzz);  
    if ( indicator == 0){                                // Note: if indicator is 0, we have a file to close/free
        fclose(fp);
        free(file_name_copy);
    }
    

}

/********gen_random_num*********/
/* random number generator, used because 
*  rand() wasn't producing random enough numbers
* 
*  code inspired by cs.yale.edu
*/
unsigned int gen_random_num(int min, int max)
{
    FILE *fp = fopen("/dev/urandom", "r"); 
    unsigned int randval; 
    fread(&randval, sizeof(randval), 1, fp); 
    fclose(fp); 
    randval = abs(randval % (max+1)) + min; 
    return randval; 
}

/*********get_random_possible**********/
/* get random number from the unit's possibles 
 * Input: unit to return a random possible number from (if any)
 * Output: a random number from the unit's possibles
 */
int get_random_possible(unit_t *unit)
{
    if ( unit == NULL ){
        fprintf(stderr, "Invalid unit passed in to get_random_possible\n");
        return -1;
    }

    int randomNum = gen_random_num(1, 9);           // generate a random number 1-9
    if (possibles_isEmpty(unit)) {                  // if the given unit has no possible values, exit
        return 0;
    }       

    while (!possibles_contain(unit, randomNum)) {   // while the current random number is not in our possibles list...
        randomNum = gen_random_num(1, 9);           // generate a new random number
    }

    return randomNum;                               // return the random number (should be in our possibles list)
}

/******* fill_puzzle *******/
/* Randomly fills in the entire puzzle, making sure sudoku rules are held 
 * *  Input: puzzle struct 
 * *  Output: true if puzzle filled properly, false otherwise 
 * */
static bool fill_puzzle(puzzle_t *puzzle)
{
    if ( puzzle == NULL ){  // check arguments
        fprintf(stderr, "Invalid puzzle passed in to fill_puzzle\n");
        return false;
    }
    unit_t* nextUnit = next_unit(puzzle);                           // get the next valid unit
    if (nextUnit == NULL) {                                         // if there is no next valid unit, exit
        return false;   
    }
    unit_t *unit = puzzle[nextUnit->row_num][nextUnit->col_num];    // access the unit at in the nextUnit's position
    
    delete_unit(nextUnit);                                          // delete the nextUnit we found

    possibles_create(puzzle, unit);                                 // generate a new possibles list    
    if (possibles_isEmpty(unit)) {                                  // if no possibles can be found...
        return false;                                               // then we can't fill our puzzle
    }

    int temp = 0; 
    while ( (temp = get_random_possible(unit)) != 0 ) {             // while we can get a number from our possibles list
        unit->val = temp;                                           // insert that number as the current unit's value

        if (fill_puzzle(puzzle) || is_puzzle_solveable(puzzle)) {   // if this entry satisfies the sudoku rules
            return true;                                            // we have successfully filled a box!
        }

        possibles_remove(unit, temp);                               // if not... remove the value from possibles and try again
    }
    unit->val = 0;                                                  // if there are no more values in our possibles list
    return false;                                                   // we have failed to fill this given box
}   


/***********copy_counters************/
/* copies all current (key, count) values into the given
*  ctrs argument
*/
static void copy_counters(void *arg, const int key, int count) 
{
    if ( arg == NULL || count < 0 ){
        fprintf(stderr, "Invalid arguments for copy_counters\n");
        return;
    }
    counters_t *result = arg; 
    counters_set(result, key, count);
}

/******* copy_puzzle *******/
/* Helper function for puzzle_iterate that copies all data values for one 
 * *  puzzle into another
 * */
void copy_puzzle(void *arg, unit_t* unit) 
{
    if ( arg == NULL || unit == NULL ){
        fprintf(stderr, "Invalid parameters for copy_puzzle\n");
        return;
    }
    puzzle_t *copy = arg;                       // cast the given arg as a puzzle struct              
    int row = unit->row_num;                    // pull out the row number from the given unit
    int col = unit->col_num;                    // pull out the column number from the given unit
    copy[row][col]->val = unit->val;            // insert into our new puzzle copy
    counters_iterate(unit->possibles, copy[row][col]->possibles, copy_counters);   // copy the possibles list
}

/******* has_one_solution *******/
/* Our best estimate of testing to see if a puzzle has one unique solution
 * *  
 * *  Given both an unsolved puzzle and its solution, it calls fill_puzzle 
 * *  on the unsolved puzzle to generate a random solution, then compares
 * *  the two puzzles to see if the random solution matches the given solution
 * * 
 * * Inputs: 
 * *      * puzzle: current puzzle struct 
 * *      * fullpuzz: solution of current puzzle struct, as generated by 
 * *                  fill_puzzle
 * * Output: 
 * *      * true if the puzzles match, false otherwise 
 * */
static bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz)
{
    if ( puzzle == NULL || fullpuzz == NULL ){
        fprintf(stderr, "Invalid parameters for has_one_solution\n");
        return false;
    }
    
    if (!is_puzzle_solveable(puzzle)) {                     // First make sure there is at least one solution
        return false;
    }

    puzzle_t *testpuzz = puzzle_new();                      // create a test puzzle to see what the current puzzle looks like
    puzzle_iterate(puzzle, testpuzz, copy_puzzle);          // copy in our current puzzle
    fill_puzzle(testpuzz); 

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) { 
            if (fullpuzz[i][j]->val != testpuzz[i][j]->val) {   // If testpuzz and fullpuzz have any different numbers...
                puzzle_delete(testpuzz); 
                return false;                                   // then there is not only one solution to the puzzle
            }
        }
    }
    puzzle_delete(testpuzz);                                    // clean up
    return true;                                                // otherwise, this is a unique solution
}

/******* hide_nums *******/
/* Randomly selects units to remove from the given puzzle 
 * *  Inputs: 
 * *     * puzzle: current puzzle struct 
 * *     * fullpuzz: the solved full version of puzzle, as generated 
 * *                 by fill_puzzle
 * *     * minshown: the minimum amount of numbers to be shown
 * * Output: 
 * *     * true if enough numbers are hidden (at least 40), false otherwise 
 * */
static bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz, int minshown)
{
    int n = 81;                                             // total number of boxes
    int row, col, number; 
    while (has_one_solution(puzzle, fullpuzz) && n > minshown) {
        row = gen_random_num(0, 8);                     // Get random position in puzzle to remove from 
        col = gen_random_num(0, 8);
        number = puzzle[row][col]->val;                 // Store that unit's val in case we need to add it back
        if (number > 0) {                               // if the number is not already zero...
            n--;                                        // then count this as one of our "hidden" boxes
        }
        
        puzzle[row][col]->val = 0;                      // "Hide" this number by reseting the value to zero
    }

    puzzle[row][col]->val = number;                     // Once its not solvable, add back the last number 

    if (n > 41) {                                       // Make sure we've removed enough numbers
        return false;                                   // otherwise, we'll need to run hide_nums again
    } 

    return true; 
}