# Sudoku Implementation Spec
### Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez 
### Dartmouth CS50, Summer 2020

### Overview

The specific data structures are defined in the sections below.

`Sudoku` supports two features: generating a new 9x9 puzzle, or solving a given 9x9 puzzle. For the latter, the program takes in a puzzle-formatted file and prints to stdout the solution, if any.

### create

### solve

`Solve` reads a puzzle-formatted file to determine whether a valid solution exists for the given file. In particular, `solve` recursively tests each possible number to determine whether such a solution exists, and returns this solution if true. If no solutions exists or if there were issues with inputs, `solve` will return the corresponding error.

`Solve` uses a *unit* and *puzzle* data structure to keep track of the values within the sudoku puzzle. In addition, `unit` also uses a *counterset* data structure to store the possible numbers each unit can take. Please see the README for definitions, or see below for further implementation.

The `solve` module implements the following methods:
(Please see pseudocode for pseudocode implementation.)
(Please note that as implemented, these methods may not be organized into
the same directory)
```c
/******* solve ********/
/* Main driver method for solve
 * Input:
 * file_name: the pathname of a puzzle-formatted file
 * Output: none (directly prints the puzzle to stdout)
 */
void solve(char* file_name);

/*******solve_puzzle********/
/* Fills in the entire puzzle (main solving method)
 * Inputs: puzzle
 * Output: true if solved, false otherwise
 */
bool solve_puzzle(puzzle_t* puzzle);

/*******first_valid_unit********/
/* Finds the first unit within a puzzle not yet filled in
 * itemfunc method to be called in puzzle_iterate
 * Inputs: pointer, current cell
 * Output: none (directly populates ptr)
*/
void first_valid_unit(void* ptr, unit_t* current_cell);

/*******next_unit********/
/* Finds the first unit within a puzzle not yet filled in
 * Inputs: puzzle
 * Output: unit
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
```

### Pseudo code for solve

The `solve.c` implementation runs as follows (using C):
1. Execute from a command line with usage syntax `./sudoku solve PUZZLE_FILE_NAME`
2. Validate its command-line arguments:
   1. Ensure `PUZZLE_FILE_NAME` is the pathname for an existing readable file, formatted as a puzzle
3. Load the index from `PUZZLE_FILE_NAME` into an internal puzzle data structure.
4. Solve the puzzle recursively.
   1. Retrieve the next fillable unit within the puzzle
   2. Until the next unit is not NULL, continue (as NULL indicates that the puzzle is solved)
   3. Create a possibles list for this unit
   4. If there are no possible numbers to input in this unit (i.e. possibls is empty)
       1. Delete the possibles list
       2. Set the value of the unit to the empty-cell value
       3. Return false as there is no solution using the current puzzle values
   5. For each possible number, p, in the unit
       1. Set the unit value to be p
       2. Solve the puzzle with the newly changed puzzle and return true if solveable
       3. Otherwise, remove the value from the list of possibles as it did not result in a solveable solution
5. Clean up and return false as there is no solution to the puzzle


### Testing plan

To test the output of `create.c` and `solve.c`, we run several hard-coded examples as welll as `fuzzquery` inputs and manually check the outputs. Both modules have their respective unit tests, as well as an integration test to test the program's functionality as a whole.

In particular, we check that `create` will create as close to a unique puzzle as possible (please see README and extended pseudo-proof for why we cannot guarantee uniqueness). 

Similarly, we check that `solve` will correctly solve a puzzle with a known solution. We also use various `fuzzquery` tests with known sudoku puzzle solutions and invalid inputs to ensure robustness. For example, we test `solve` on puzzles with different amounts of units filled in to test the accuracy of backtracing/the recursive process. 

Please see `DESIGN.md` for more testing specific examples.