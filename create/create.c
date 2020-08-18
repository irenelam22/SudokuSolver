/*

Assignment: Final project – Group KIDD
Members: David Kantor, David Perez Gonzalez, Irene Lam, and Kelly Westkaemper
*/

#include <stdio.h>
#include <stdlib.h>

// function prototypes

int main(const int argc, const char *argv[])
{

    // 1. create empty puzzle struct 
    puzzle_t *puzzle = puzzle_new(); 

    // 2. pass that struct to solve to get a full puzzle 
        // this is assuming that giving solve an empty puzzle will result 
        // in a randomly generated selection of numbers (i.e. solve picks numbers at random)
    puzzle = solve(puzzle); 

    // 3. keep removing numbers while there's still only one solution
    puzzle = hide_nums(puzzle); 

    // 4. print finished puzzle to standard output 
    print_puzzle(puzzle); 

    // 5. clean everything up from memory 
    delete_puzzle(puzzle); 

}

puzzle_t *hide_nums(puzzle_t *puzzle)
{
    int n = 81; 
    int row, col, number; 
    // while puzzle is solvable: 
        // could have another specification that stops once
        // we've removed a certain number of units 
        // (possible way of deciding difficulty level of puzzle)
    while (solve(puzzle)) {
        // get random position in puzzle to remove from 
        row = rand() % 9; 
        col = rand() % 9; 
        // store that unit's value in case we need to add it back
        number = puzzle[row][col]->value; 
        // delete that number from the puzzle 
        puzzle[row][col]->value = 0; 
        n--; 
    }
    // Once its not solvable, add back the last number 
    puzzle[row][col]->value = number; 
    return puzzle; 
}