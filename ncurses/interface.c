#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../common/puzzle.c"
#include "../common/unit.c"
#include "../solve/solve.h"

#define ORIGINAL_PAIR 0             // Original numbers in puzzle
#define NEW_PAIR 1                  // Numbers to be modified (originally 0)
#define PARENTHESES_PAIR 3          // Paranthesis designating where the user is

void print_help()
{
    mvaddstr(0, 30, "Help Manual:");
    mvaddstr(1, 30, "-----------");
    mvaddstr(2, 30, "Units displayed in white are part of the original puzzle");
    mvaddstr(3, 30, "Units displayed in yellow can be edited");
    mvaddstr(4, 30, "Numbers surrounded by paranthesis represent the current cell you're on");
    mvaddstr(5, 30, "See the list of possible numbers on the bottom");
    mvaddstr(7, 30, "Instructions:");
    mvaddstr(8, 30, "-----------");
    mvaddstr(9, 30, "Press arrow keys to move left/right/up/down");
    mvaddstr(10, 30, "Press integers 1 through 9 to insert");
    mvaddstr(11, 30, "Press 0 or d to delete the value in the current unit");
    mvaddstr(12, 30, "Press f to jump to the first unfilled unit");
    mvaddstr(13, 30, "Press c to complete the remaining cells if possible");
    mvaddstr(14, 30, "Press q to quit");
}

// Pretty print method
void pprint(puzzle_t *puzzle, unit_t* current_unit)
{
    int MAX_COL = 23;
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

        counters_delete(current_unit -> possibles);
        current_unit -> possibles = NULL;
        possibles_create(puzzle, current_unit);
        if (!(current_unit -> is_original)) {
            char* possible_listing = possibles_print_ncurses(current_unit);
            printw("%s", possible_listing);
            free(possible_listing);
        }
        
    }
    print_help();
}

int main(void)
{
    char* filename = "../puzzlefiles/easy.txt";
    FILE* puzzle_file = fopen(filename, "r");
    puzzle_t* puzzle = puzzle_load(puzzle_file);
    // puzzle_print(stdout, puzzle);

    // sleep(1);
    initscr();
    cbreak();
    noecho();

    // Coloring puzzle
    start_color();
    init_pair(ORIGINAL_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(NEW_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PARENTHESES_PAIR, COLOR_MAGENTA, COLOR_BLACK);

    // keypad Support 
    keypad(stdscr, TRUE);
    unit_t* start = next_unit(puzzle);
    start -> possibles = NULL;
    unit_t* ptr = puzzle_get_unit(puzzle, start -> row_num, start -> col_num);
    delete_unit(start);

    int count = 0;
    while (true) {
        clear();
        pprint(puzzle, ptr);
        refresh();
        int ch = getch();
        int row = ptr -> row_num;
        int col = ptr -> col_num;

        // User mouse movement
        switch(ch) {
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
            case 'f':
                start = next_unit(puzzle);
                if (start == NULL) {
                    mvaddstr(13, 2, "There is no next in this puzzle!");
                } else {
                    ptr = puzzle_get_unit(puzzle, start -> row_num, start -> col_num);
                    start -> possibles = NULL;
                    delete_unit(start);
                }
                break;
            case '0':
            // case 'd':
                if (!(ptr -> is_original)) {
                    ptr -> val = 0;
                }
                break;
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
            case 'c':
                if (!solve_puzzle(puzzle)) {
                    mvaddstr(14, 2, "There is no solution to this puzzle (at thus current state)");
                }
                break;
            default:
                break;
        }
        // if (is_puzzle_solveable(puzzle)) {
        //     mvaddstr(5, 30, "Congratulations! You've solved the puzzle!");
        //     break;
        // }

        // Quit
        if(ch == 'q') {
            mvaddstr(12, 1, "q=quit");
            break;
        } 
        else {
            printw("Press Left arrow or infinite loop %d - %c", ++count, ch);
        }
    }

    // Replace with final puzzle/message
    refresh();
    puzzle_delete(puzzle);
    
    endwin();
    exit(0);
}
