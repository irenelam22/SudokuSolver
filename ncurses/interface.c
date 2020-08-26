#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../common/puzzle.c"
#include "../common/unit.c"


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
                mvaddch(i + i / 3, j, '0' + puzzle[i][j/2 - j/8] -> val);
            }
        }
    }

    if (current_unit != NULL) {
        int curr_row = current_unit -> row_num;
        int curr_col = current_unit -> col_num;
        mvaddch(curr_row + curr_row/3, 2* (curr_col -1 + curr_col* 2/7), '(');
        mvaddch(curr_row + curr_row/3, 2* (curr_col + curr_col * 2/7), ')');
    }
}

int main(void)
{
    char* filename = "../puzzlefiles/easy.txt";
    FILE* puzzle_file = fopen(filename, "r");
    puzzle_t* puzzle = puzzle_load(puzzle_file);
    puzzle_print(stdout, puzzle);

    sleep(1);
    initscr();
    cbreak();
    noecho();
    clear();

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
        // replace with switch case
        // Currently exits
        switch(ch) {
            case KEY_LEFT:
                if (row > 1) {
                    ptr = puzzle_get_unit(puzzle, row, (col + 8) % 9 );
                    move(12, 1);
                    // printw("Current unit: %d", counters_get(ptr->possibles, 0));
                    print_unit(ptr);
                }
                break;
            case KEY_RIGHT:
                if (row < MAX_COL) {
                    ptr = puzzle_get_unit(puzzle, row, (col + 1) % 9 );
                }
                break;
            case KEY_UP:
                if (col > 0) {
                    ptr = puzzle_get_unit(puzzle, (row + 8) % 9, col);
                }
                break;
            case KEY_DOWN:
                if (col < MAX_ROW) {
                    ptr = puzzle_get_unit(puzzle, (row + 1) % 9, col);
                }
                break;
            default:
                break;
        }
        if(ch == 'q') {
            mvaddstr(12, 1, "q=quit");
            break;
        } 
        else {
            move(12, 1);
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
