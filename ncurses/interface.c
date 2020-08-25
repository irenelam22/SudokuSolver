#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../common/puzzle.c"

// Pretty print method
void pprint(puzzle_t *puzzle, unit_t* current_unit)
{
    int MAX_ROW = 9;
    int MAX_COL = 23;
    for (int i = 0; i < MAX_ROW; i++) {
        if (i == 3 || i == 6) {
            mvaddstr(i + i / 3 - 1, 0, "-----------------------");
            // fprintf(fp, "---------------------\n"); 
        }
        
        for (int j = 0; j < MAX_COL; j++) {
            if (j == 7 || j == 15) {
                mvaddch(i + i/3, j, '|');
            }
            else if (j%2 == 1) {
                mvaddch(i + i / 3, j, '?');
            }
        }
    }

    if (current_unit != NULL) {
        int curr_row = current_unit -> row_num;
        int curr_col = current_unit -> col_num;
        mvaddstr(curr_row, curr_col-1, '(');
        mvaddstr(curr_row, curr_col+1, ')');
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

    // make sure terminal screen is tall/wide enough
    int maxlines = LINES - 1;
    int maxcols = COLS - 1;

    pprint(puzzle, NULL);
    refresh();

    unit_t* ptr = next_unit(puzzle);
    int count = 0;
    while (true) {
        pprint(puzzle, NULL);
        refresh();
        int ch = getch();
        // replace with switch case
        // Currently exits
        if(ch == KEY_LEFT || ch == 'q') {
            printw("Left arrow is pressed\n");
            break;
        } else {
            char* num = assertp(malloc(sizeof(count)+1), "pagesaver ID");
            sprintf(num, "%d", count);
            ++count;
            printw("Press Left arrow or infinite loop %s - %c\n", num, ch);
            free(num);
        }
    }

    // Replace with final puzzle/message
    mvaddstr(maxlines, 2, "Final Puzzle: (currently not implemented, press randomly to exit");
    refresh();
    getch();
    endwin();
    exit(0);
}
