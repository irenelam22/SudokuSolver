#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../common/puzzle.c"

void pprint(puzzle_t *puzzle, unit_t* current_unit)
{
    int MAX_ROW = 9;
    for (int i = 0; i < MAX_ROW; i++) {
        if (i == 3 || i == 6) {
            mvaddstr(i + i / 3 - 1, 0, "----------------------");
            // fprintf(fp, "---------------------\n"); 
        }
        for (int j = 0; j < MAX_COL; j++) {
            if (j == 3 || j == 6) {
                mvaddch(i + i / 3, 1 + j + 2 * j / 3 + 1, '|');
                // fprintf(fp, "| "); 
            }
            mvaddch(j + j / 3, 1 + 2 * i + 2 * (i - 1) / 3, '?');
            // mvaddch(j, i, ' ');
            // fprintf(fp, "%d ", get_unit_val(puzzle[i][j])); 
        }
        // fprintf(fp, "\n");
    }

    if (current_unit != NULL) {
        // print paren around position
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

    mvaddstr(maxlines, 2, "Final Puzzle: (currently not implemented, press randomly to exit");
    refresh();
    getch();
    endwin();
    exit(0);
}
