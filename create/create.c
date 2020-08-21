/*

Assignment: Final project – Group KIDD
Members: David Kantor, David Perez Gonzalez, Irene Lam, and Kelly Westkaemper
*/

#include <stdio.h>
#include <stdlib.h>
#include "../solve/solve.h"
#include "../common/puzzle.h"
#include "../common/unit.h"

// function prototypes

bool fill_puzzle(puzzle_t *puzzle); 
bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz); 
bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz); 
void copy_puzzle(void *arg, unit_t* unit); 

int main(const int argc, const char *argv[])
{
    // Check arguments 
    FILE *fp; 
    if (argc == 2) {
        char *filename = malloc(strlen(argv[1])+1); 
        if (filename == NULL) {
            fprintf(stderr, "Failed to allocate memory for file\n"); 
            return 2; 
        }
        strcpy(filename, argv[1]); 
        if ( (fp = fopen(filename, "w")) == NULL) {
            fprintf(stderr, "%s is not a writeable file\n", filename); 
            free(filename); 
            return 2; 
        }
    }
    else if (argc == 1) {
        fp = stdout; 
    }
    else {
        fprintf(stderr, "Usage: ./create [filename]\n"); 
        return 1; 
    }

    // Create empty puzzle and randomly fill in all the values 
    puzzle_t *puzzle = puzzle_new(); 
    fill_puzzle(puzzle); 

    // Store the completed puzzle for later
    puzzle_t *fullpuzz = puzzle_new(); 
    puzzle_iterate(puzzle, fullpuzz, copy_puzzle); 

    // Keep removing numbers while there's still only one solution
    // and while we have <= 41 showing numbers
    while (!hide_nums(puzzle, fullpuzz)) {
        puzzle_iterate(fullpuzz, puzzle, copy_puzzle); 
    }

    // Print finished puzzle to provided file (or stdout)
    puzzle_print(fp, puzzle); 

    // Clean everything up from memory 
    puzzle_delete(puzzle);
    puzzle_delete(fullpuzz);  
    if (argc == 2) {fclose(fp);}

}

/********gen_random_num*********/
/* random number generator, used because 
*  rand() wasn't producing random enough numbers
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
*/
int get_random_possible(unit_t *unit)
{
    int randomNum = gen_random_num(1, 9); 
    // printf("first random num = %d\n", randomNum); 
    if (possibles_isEmpty(unit)) {return 0;}
    while (!possibles_contain(unit, randomNum)) {
        // printf("random num = %d\n", randomNum); 
        randomNum = gen_random_num(1, 9); 
    }
    // printf("successful random num = %d\n", randomNum); 
    return randomNum; 
}

/*******fill_puzzle************/
/* Randomly fills in a puzzle, making sure sudoku rules are held
*/
bool fill_puzzle(puzzle_t *puzzle)
{
    unit_t* nextUnit = next_unit(puzzle);
    if (nextUnit == NULL) {
        return false;
    }
    unit_t *unit = puzzle[nextUnit->row_num][nextUnit->col_num];
    
    delete_unit(nextUnit); 
    // printf("unit row = %d, col = %d\n", unit->row_num, unit->col_num); 
    
    // If nothing is possible, backtrace
    possibles_create(puzzle, unit); 
    if (possibles_isEmpty(unit)) {
        return false;
    }

    // If there's at least one possible value, 
    // get a random number from list of possibles 
    // updating_possibles(puzzle, unit); 
    int temp = 0; 
    while ( (temp = get_random_possible(unit)) != 0 ) {
        unit->val = temp; 
        // Move to the next number
        if (fill_puzzle(puzzle) || is_puzzle_solveable(puzzle)) {
            return true; 
        }
        // If we got an impossible puzzle, backtrace 
        possibles_remove(unit, temp); 
    }
    unit->val = 0;
    return false;
}


/***********copy_counters************/
/* copies all current (key, count) values into the given
*  ctrs argument
*/
static void copy_counters(void *arg, const int key, int count) 
{
    counters_t *result = arg; 
    counters_set(result, key, count);
}

/*********copy_puzzle***********/
/* copy values and possibles of current puzzle into provided puzzle_t argument
*/
void copy_puzzle(void *arg, unit_t* unit)
{
    puzzle_t *copy = arg; 
    int row = unit->row_num;
    int col = unit->col_num; 
    copy[row][col]->val = unit->val;   
    counters_iterate(unit->possibles, copy[row][col]->possibles, copy_counters);  
}

/*************has_one_solution***********/
/* tests to see if there's more than one solution by trying 
*  to fill in the hidden values in the current puzzle, then 
*  comparing that to the full puzzle
*/
bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz)
{
    // First make sure theres > 0 solutions
    if (!is_puzzle_solveable(puzzle)) {return false;}

    // We don't want to modify the actual puzzle, so create testpuzz
    // to see what the current solution to the puzzle looks like 
    puzzle_t *testpuzz = puzzle_new(); 
    puzzle_iterate(puzzle, testpuzz, copy_puzzle);
    fill_puzzle(testpuzz); 

    // If testpuzz and fullpuzz have any different numbers, there must be more 
    // than one solution to the puzzle
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) { 
            if (fullpuzz[i][j]->val != testpuzz[i][j]->val) {
                puzzle_delete(testpuzz); 
                return false; 
            }
        }
    }
    puzzle_delete(testpuzz); 
    return true; 
}

/**********hide_nums************/
/* hide numbers in a sudoku one by one, making sure there's still
*  only one solution
* 
*  if the finished puzzle has <= 41 numbers showing by the end, it returns false
*/
bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz)
{
    int n = 81; 
    int row, col, number; 
    while (has_one_solution(puzzle, fullpuzz) && n > 20) {
        // Get random position in puzzle to remove from 
        row = gen_random_num(0, 8); 
        col = gen_random_num(0, 8);
        // Store that unit's val in case we need to add it back
        number = puzzle[row][col]->val; 
        if (number > 0) {n--;}
        // Delete that number from the puzzle 
        puzzle[row][col]->val = 0; 
    }
    // Once its not solvable, add back the last number 
    puzzle[row][col]->val = number; 
    // Make sure we've removed enough numbers
        // otherwise, we'll need to run hide_nums again
    if (n > 41) {return false;} 
    return true; 
}