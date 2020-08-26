#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../common/puzzle.c"
#include "../common/unit.c"

#define ORIGINAL_PAIR 0             // Original numbers in puzzle
#define NEW_PAIR 1                  // Numbers to be modified (originally 0)
#define PARENTHESES_PAIR 3          // Paranthesis designating where the user is

// Pretty print method
void pprint(puzzle_t *puzzle, unit_t* current_unit)
{
    
    // TODO: print possibles, insert number, delete, help, get next unit (n), try mouse
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

        possibles_create(puzzle, current_unit);
        if (!(current_unit -> is_original)) {
            printw("%s", possibles_print_ncurses(current_unit));
        }
        
    }
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
    clear();

    // Coloring puzzle
    start_color();
    init_pair(ORIGINAL_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(NEW_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PARENTHESES_PAIR, COLOR_MAGENTA, COLOR_BLACK);

    // keypad Support 
    keypad(stdscr, TRUE);
    pprint(puzzle, NULL);
    refresh();

    unit_t* ptr = next_unit(puzzle);
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
                ptr = puzzle_get_unit(puzzle, row, (col + 8) % 9);
                break;
            case KEY_RIGHT:
                ptr = puzzle_get_unit(puzzle, row, (col + 1) % 9);
                break;
            case KEY_UP:
                ptr = puzzle_get_unit(puzzle, (row + 8) % 9, col);
                break;
            case KEY_DOWN:
                ptr = puzzle_get_unit(puzzle, (row + 1) % 9, col);
                break;
            default:
                break;
        }

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
    mvaddstr(LINES - 1, 2, "Final Puzzle: (currently not implemented, press randomly to exit");
    refresh();
    getch();
    endwin();
    exit(0);
}
