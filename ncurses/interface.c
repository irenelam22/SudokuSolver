/*
 * interface.c -- EXTRA CREDIT terminal interaction
 *
 * This program is essentially an ncurses interactive sudoku game, in which 
 * users can navigate through the puzzle using their keyboard. The program 
 * displays the possibles list for each editable unit (i.e. not part of the 
 * original puzzle) and will display a congratulations message when complete.
 * 
 * Dartmouth CS50, Summer 2020
 */
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../common/puzzle.c"
#include "../common/unit.c"
#include "../solve/solve.h"

// Color pairs
#define ORIGINAL_PAIR 0             // Original numbers in puzzle
#define NEW_PAIR 1                  // Numbers to be modified (originally 0)
#define PARENTHESES_PAIR 3          // Paranthesis designating where the user is

// Prints the help manual detailing the instructions
void print_help()
{
    mvaddstr(0, 35, "Help Manual:");
    mvaddstr(1, 35, "-----------");
    mvaddstr(2, 35, "Units displayed in white are part of the original puzzle");
    mvaddstr(3, 35, "Units displayed in yellow can be edited");
    mvaddstr(4, 35, "Numbers surrounded by paranthesis represent the current cell you're on");
    mvaddstr(5, 35, "See the list of possible numbers below the puzzle (only displays for yellow units)");
    mvaddstr(7, 35, "Instructions:");
    mvaddstr(8, 35, "-----------");
    mvaddstr(9, 35, "Press arrow keys or WASD to move left/right/up/down");
    mvaddstr(10, 35, "Press integers 1 through 9 to insert");
    mvaddstr(11, 35, "Press 0 to delete the value in the current unit");
    mvaddstr(12, 35, "Press n to jump to the first unfilled unit");
    mvaddstr(13, 35, "Press c to solve the puzzle if possible");
    mvaddstr(14, 35, "Press q to quit");
}

/******* pprint ********/
/** Pretty prints the entire program
 * Inputs: puzzle to print, current unit the player is on
 * Output: none (prints to terminal)
 */
void pprint(puzzle_t *puzzle, unit_t* current_unit)
{
    int MAX_COL = 23;

    // Print the puzzle
    for (int i = 0; i < MAX_ROW; i++) {
        if (i == 3 || i == 6) {
            mvaddstr(i + i / 3 - 1, 0, "-----------------------");
        }
        
        for (int j = 0; j < MAX_COL; j++) {
            if (j == 7 || j == 15) {
                mvaddch(i + i/3, j, '|');
            }
            else if (j%2 == 1) {
                unit_t* ptr = puzzle[i][j/2 - j/8];
                attron(COLOR_PAIR(!(ptr -> is_original)));
                mvaddch(i + i / 3, j, '0' + ptr -> val);
                attroff(COLOR_PAIR(!(ptr -> is_original)));
            }
        }
    }    

    // Placing paranthesis
    if (current_unit != NULL) {
        attron(COLOR_PAIR(PARENTHESES_PAIR));
        int curr_row = current_unit -> row_num;
        int curr_col = current_unit -> col_num;
        mvaddch(curr_row + curr_row/3, 2* (curr_col + curr_col/3), '(');
        mvaddch(curr_row + curr_row/3, 2* (curr_col + curr_col/3 + 1), ')');
        attroff(COLOR_PAIR(PARENTHESES_PAIR)); 

        // To offplace cursor
        move(12, 1);

        // Creating the possibles list for each unit
        counters_delete(current_unit -> possibles);
        current_unit -> possibles = NULL;
        possibles_create(puzzle, current_unit);
        
        // Printing possibles list if any
        if (!(current_unit -> is_original)) {
            char* possible_listing = possibles_print_ncurses(current_unit);
            printw("%s", possible_listing);
            free(possible_listing);
        }
        
    }
    print_help();

    // Checking whether the puzzle is finished and printing corresponding congratulations
    if (is_puzzle_finished(puzzle)) {
            attron(COLOR_PAIR(NEW_PAIR));
            mvaddstr(LINES - 1, 2, "CONGRATULATIONS! You've solved the puzzle! (Press q to quit)");
            attroff(COLOR_PAIR(NEW_PAIR));
        } 
}

/******* splash_screen ********/
/**
 * Prints a spalsh screen of our team :)
 * All credits to patorjk.com for translating the text to ASCII characters
 * Inputs/Outputs: none
 */
void splash_screen()
{
    attron(COLOR_PAIR(PARENTHESES_PAIR));
    mvaddstr(1, 3, "                                       /$$           /$$                             ");
    mvaddstr(2, 3, "                                      | $$          | $$                             ");
    mvaddstr(3, 3, "              /$$$$$$$ /$$   /$$  /$$$$$$$  /$$$$$$ | $$   /$$ /$$   /$$             ");
    mvaddstr(4, 3, "             /$$_____/| $$  | $$ /$$__  $$ /$$__  $$| $$  /$$/| $$  | $$             ");
    mvaddstr(5, 3, "            |  $$$$$$ | $$  | $$| $$  | $$| $$  \\ $$| $$$$$$/ | $$  | $$             ");
    mvaddstr(6, 3, "             \\____  $$| $$  | $$| $$  | $$| $$  | $$| $$_  $$ | $$  | $$             ");
    mvaddstr(7, 3, "             /$$$$$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$/| $$ \\  $$|  $$$$$$/             ");
    mvaddstr(8, 3, "            |_______/  \\______/  \\_______/ \\______/ |__/  \\__/ \\______/              ");

    mvaddstr(10, 3, " /$$$$$$$$                                      /$$   /$$ /$$$$$$ /$$$$$$$  /$$$$$$$ ");
    mvaddstr(11, 3, "|__  $$__/                                     | $$  /$$/|_  $$_/| $$__  $$| $$__  $$");
    mvaddstr(12, 3, "   | $$  /$$$$$$   /$$$$$$  /$$$$$$/$$$$       | $$ /$$/   | $$  | $$  \\ $$| $$  \\ $$");
    mvaddstr(13, 3, "   | $$ /$$__  $$ |____  $$| $$_  $$_  $$      | $$$$$/    | $$  | $$  | $$| $$  | $$");
    mvaddstr(14, 3, "   | $$| $$$$$$$$  /$$$$$$$| $$ \\ $$ \\ $$      | $$  $$    | $$  | $$  | $$| $$  | $$");
    mvaddstr(15, 3, "   | $$| $$_____/ /$$__  $$| $$ | $$ | $$      | $$\\  $$   | $$  | $$  | $$| $$  | $$");
    mvaddstr(16, 3, "   | $$|  $$$$$$$|  $$$$$$$| $$ | $$ | $$      | $$ \\  $$ /$$$$$$| $$$$$$$/| $$$$$$$/");
    mvaddstr(17, 3, "   |__/ \\_______/ \\_______/|__/ |__/ |__/      |__/  \\__/|______/|_______/ |_______/ ");
    mvaddstr(LINES - 2, COLS - 40, "ASCII art created using patorjk.com");
    mvaddstr(LINES - 1, COLS - 40, "Press any character to continue...");
    attroff(COLOR_PAIR(PARENTHESES_PAIR));
    getch();
    clear();
}

/**
 * validates the inputs for the main
 * Inputs: number of inputs, filename of puzzle
 * Output: true is success, false otherwise
 */
bool validate_inputs(int num_inputs, char* filename)
{
    if (num_inputs > 2) {
        fprintf(stderr, "Too many inputs: Please only pass one puzzle-generated file\n");
        return false;
    }
    if (num_inputs < 2) {
        fprintf(stderr, "Usage: ./interface puzzle-formatted-file\n");
        return false;
    }
    FILE* puzzle_file = fopen(filename, "r");
    if (puzzle_file == NULL) {
        fprintf(stderr, "Puzzle file passed to interface is either not readable or does not exist\n");
        return false;
    }
    puzzle_t* puzzle = puzzle_load(puzzle_file);
    if (puzzle == NULL) {
        fprintf(stderr, "Please pass a valid, puzzle-formatted file\n");
        fclose(puzzle_file);
        return false;
    }
    fclose(puzzle_file);
    return true;
}

/******* main ********/
/** Main method to run the program
 * Manages the user's actions on the puzzle 
 * Inputs: none
 * Output: 0 if success, otherwise failure
 */
int main(const int argc, char *argv[])
{
    // Read the file
    char* filename = "../puzzlefiles/easy.txt";
    FILE* puzzle_file = fopen(filename, "r");
    puzzle_t* puzzle = puzzle_load(puzzle_file);
    fclose(puzzle_file);

    // Initialize ncurses library
    initscr();
    cbreak();
    noecho();

    // Color the puzzle
    start_color();
    init_pair(ORIGINAL_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(NEW_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PARENTHESES_PAIR, COLOR_MAGENTA, COLOR_BLACK);

    splash_screen();

    // Keypad Support 
    keypad(stdscr, TRUE);

    // Find the next unit and initialize
    unit_t* start = next_unit(puzzle);
    start -> possibles = NULL;
    unit_t* ptr = puzzle_get_unit(puzzle, start -> row_num, start -> col_num);
    delete_unit(start);

    // Run the program
    while (true) {
        pprint(puzzle, ptr);
        refresh();
        int ch = getch();
        int row = ptr -> row_num;
        int col = ptr -> col_num;
        clear();

        switch(ch) {
            // User mouse movement
            case KEY_LEFT:
            case 'a':
                ptr = puzzle_get_unit(puzzle, row, (col + 8) % 9);
                break;
            case KEY_RIGHT:
            case 'd':
                ptr = puzzle_get_unit(puzzle, row, (col + 1) % 9);
                break;
            case KEY_UP:
            case 'w':
                ptr = puzzle_get_unit(puzzle, (row + 8) % 9, col);
                break;
            case KEY_DOWN:
            case 's':
                ptr = puzzle_get_unit(puzzle, (row + 1) % 9, col);
                break;

            // Go to the first unit (if any)
            case 'n':
                start = next_unit(puzzle);
                if (start == NULL) {
                    mvaddstr(LINES - 2, 2, "There is no next in this puzzle!");
                } else {
                    ptr = puzzle_get_unit(puzzle, start -> row_num, start -> col_num);
                    start -> possibles = NULL;
                    delete_unit(start);
                }
                break;
            
            // Delete
            case '0':
                if (!(ptr -> is_original)) {
                    ptr -> val = 0;
                }
                break;
            
            // Insert
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (!(ptr -> is_original)) {
                    ptr -> val = ch - '0';
                } else {
                    mvaddstr(14, 2, "attempt to modify original cell");
                }
                break;
            
            // Solve the puzzle
            case 'c':
                if (!solve_puzzle(puzzle)) {
                    mvaddstr(LINES-1, 2, "There is no solution to this puzzle (at thus current state)");
                }
                break;
            default:
                break;
        }

        // Quit
        if(ch == 'q') {
            break;
        }
    }

    refresh();
    puzzle_delete(puzzle);
    
    endwin();
    exit(0);
}
