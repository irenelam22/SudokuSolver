#include "puzzle.h"
#include "unit.h"

// Function prototype
int next_unit_test();

int main(const int argc, const char *argv[])
{
    next_unit_test(); 
    return 0;
}

int next_unit_test() 
{
    // Basic functionality test
    FILE* file1 = fopen("../puzzlefiles/easy.txt", "r");
    puzzle_t* puzzle = puzzle_load(file1); 
    unit_t* nextUnit = next_unit(puzzle);
    unit_t* ans = puzzle[1][2];
    bool test1 = (ans == nextUnit);
    if (!test1) {
        fprintf(stderr, "Next unit 1 failed on easy.txt");
    }

    nextUnit = next_unit(puzzle);
    unit_t ans2 = {
        .val = 0,
        .unit_num = 6,
        .row_num = 1,
        .col_num = 5,
        .box_num = 2,
    };
    bool test2 = (ans2.val == nextUnit -> val) && \
    (ans2.row_num == nextUnit -> row_num) && \
    (ans2.col_num == nextUnit -> col_num);
    if (!test2) {
        fprintf(stderr, "Next unit 2 failed on easy.txt");
    }

    // Testing on a completed puzzle (no next unit)
    FILE* file2 = fopen("../puzzlefiles/easyans.txt", "r");
    puzzle_t* filled_puzzle = puzzle_load(file2); 
    unit_t* filled_unit = next_unit(filled_puzzle);
    if (filled_unit != NULL){
        fprintf(stderr, "Next unit on a filled puzzle failed");
    }
    return 0;
}