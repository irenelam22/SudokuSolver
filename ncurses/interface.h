/*
 * interface.h -- EXTRA CREDIT terminal interaction
 *
 * This program is essentially an ncurses interactive sudoku game, in which 
 * users can navigate through the puzzle using their keyboard. The program 
 * displays the possibles list for each editable unit (i.e. not part of the 
 * original puzzle) and will display a congratulations message when complete.
 * 
 * Please see the README for more details
 * 
 * Dartmouth CS50, Summer 2020
 */

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../common/puzzle.c"

// Prints the help manual detailing the instructions
void print_help();

/******* pprint ********/
/** Pretty prints the entire program
 * Inputs: puzzle to print, current unit the player is on
 * Output: none (prints to terminal)
 */
void pprint(puzzle_t *puzzle, unit_t* current_unit);

/******* splash_screen ********/
/**
 * Prints a spalsh screen of our team :)
 * All credits to patorjk.com for translating the text to ASCII characters
 * Inputs/Outputs: none
 */
void splash_screen();

/**
 * validates the inputs for the main
 * Inputs: number of inputs, filename of puzzle
 * Output: puzzle on success, NULL otherwise
 */
puzzle_t* validate_inputs(int num_inputs, char* filename);

/******* main ********/
/** Main method to run the program
 * Manages the user's actions on the puzzle 
 * Inputs: none
 * Output: 0 if success, otherwise failure
 */
int main(const int argc, char *argv[]);
