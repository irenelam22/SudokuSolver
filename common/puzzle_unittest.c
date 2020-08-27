/*
puzzle_unittest -- unit testing file for puzzle methods

Currently only tests methods I used for solve (Irene)

Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/

#include "puzzle.h"
#include "unit.h"
#include "../libcs50/memory.h"

int next_unit_test() 
{
    // Basic functionality test
    FILE* file1 = fopen("../puzzlefiles/easy.txt", "r");
    puzzle_t* puzzle = puzzle_load(file1); 
    fclose(file1);
    
    unit_t* nextUnit = next_unit(puzzle);
    nextUnit -> possibles = NULL;
    unit_t ans1 = {
        .val = 0,
        .unit_num = 2,
        .row_num = 0,
        .col_num = 1,
        .box_num = 2,
    };
    bool test1 = (ans1.val == nextUnit -> val) && \
    (ans1.row_num == nextUnit -> row_num) && \
    (ans1.col_num == nextUnit -> col_num);
    if (!test1) {
        fprintf(stderr, "Next unit 1 failed on easy.txt\n");
        delete_unit(nextUnit);
        puzzle_delete(puzzle);
        fclose(file1);
        return 1;
    }

    puzzle[nextUnit -> row_num][nextUnit -> col_num] -> val = 5;
    delete_unit(nextUnit);
    nextUnit = next_unit(puzzle);
    nextUnit -> possibles = NULL;
    unit_t ans2 = {
        .val = 0,
        .unit_num = 6,
        .row_num = 0,
        .col_num = 5,
        .box_num = 2,
    };
    bool test2 = (ans2.val == nextUnit -> val) && \
    (ans2.row_num == nextUnit -> row_num) && \
    (ans2.col_num == nextUnit -> col_num);
    delete_unit(nextUnit);
    puzzle_delete(puzzle);
    if (!test2) {
        fprintf(stderr, "Next unit 2 failed on easy.txt\n");
        return 1;
    }
    return 0;
}

// Testing on a completed puzzle (no next unit)
int completed_next_unit() 
{
    FILE* file2 = fopen("../puzzlefiles/easyans.txt", "r");
    puzzle_t* filled_puzzle = puzzle_load(file2); 
    fclose(file2);

    unit_t* filled_unit = next_unit(filled_puzzle);
    if (filled_unit != NULL){
        fprintf(stderr, "Next unit on a filled puzzle failed\n");
        puzzle_delete(filled_puzzle);
        delete_unit(filled_unit);
        return 1;
    }
    
    puzzle_delete(filled_puzzle);
    return 0;
}

int possibles_update_test()
{
    FILE* file3 = fopen("../puzzlefiles/medium.txt", "r");
    puzzle_t* puzzle = puzzle_load(file3); 
    fclose(file3);

    unit_t* nextUnit = next_unit(puzzle);
    if (nextUnit == NULL) {
        fprintf(stderr, "Invalid next unit in possibles_update_test\n");
        return 1;
    }

    unit_t *unit = puzzle[nextUnit -> row_num][nextUnit -> col_num];
    nextUnit -> possibles = NULL;
    counters_delete(unit -> possibles);
    delete_unit(nextUnit); 

    possibles_create(puzzle, unit);
    counters_t* set = unit -> possibles;
    bool ans1 = (counters_get(set, 1) == 0) && (counters_get(set, 2) == 0) && \
    (counters_get(set, 3) == 0) && (counters_get(set, 4) == 0) && \
    (counters_get(set, 5) == 1) && (counters_get(set, 6) == 0) && \
    (counters_get(set, 7) == 1) && (counters_get(set, 8) == 1) && \
    (counters_get(set, 9) == 0);

    counters_delete(unit -> possibles);
    if (!ans1) {
        fprintf(stderr, "Possibles_update_test failed\n");
        puzzle_delete(puzzle);
        return 1;
    }

    puzzle[0][2] -> val = 5;
    possibles_create(puzzle, unit);
    counters_t* set2 = unit -> possibles;

    bool ans2 = (counters_get(set2, 1) == 0) && (counters_get(set2, 2) == 0) && \
    (counters_get(set2, 3) == 0) && (counters_get(set2, 4) == 0) && \
    (counters_get(set2, 5) == 0) && (counters_get(set2, 6) == 0) && \
    (counters_get(set2, 7) == 1) && (counters_get(set2, 8) == 1) && \
    (counters_get(set2, 9) == 0);

    puzzle_delete(puzzle);
    if (!ans2) {
        fprintf(stderr, "Possibles_update_test failed after updating value\n");
        return 1;
    }
    return 0;
}

// Used only in iterative appraoch (Which is not implemented)
// May considering deleting this method altogether
int solveable_test()
{
    FILE* file5 = fopen("../puzzlefiles/badpuzzle.txt", "r");
    puzzle_t* bad_puzzle = puzzle_load(file5); 
    fclose(file5);

    if (is_puzzle_solveable(bad_puzzle)) {
        puzzle_delete(bad_puzzle);
        fprintf(stderr, "Solveable failed for badtest.txt\n");
        return 1;
    }
    puzzle_delete(bad_puzzle);
    return 0;
}

int possibles_print()
{
    FILE* file6 = fopen("../puzzlefiles/medium.txt", "r");
    puzzle_t* puzzle = puzzle_load(file6); 
    fclose(file6);

    unit_t* nextUnit = next_unit(puzzle);
    if (nextUnit == NULL) {
        fprintf(stderr, "Invalid next unit in possibles_print\n");
        return 1;
    }

    unit_t *unit = puzzle[nextUnit -> row_num][nextUnit -> col_num];
    nextUnit -> possibles = NULL;
    counters_delete(unit -> possibles);
    delete_unit(nextUnit); 

    possibles_create(puzzle, unit);
    printf("%s", possibles_print_ncurses(unit));
    puzzle_delete(puzzle);
    return 0;
}

int finish_puzzle_test()
{
    FILE* file7 = fopen("../puzzlefiles/medium.txt", "r");
    puzzle_t* puzzle = puzzle_load(file7); 
    fclose(file7);

    if (is_puzzle_finished(puzzle)) {
        fprintf(stderr,"Puzzle finish incorrectly for unsolved puzzle\n");
        return 1;
    }

    FILE* file8 = fopen("../puzzlefiles/easyans.txt", "r");
    puzzle_t* puzzle2 = puzzle_load(file8); 
    fclose(file8);

    if (is_puzzle_finished(puzzle2)) {
        fprintf(stderr, "Puzzle finished incorrectly for answer puzzle\n");
        return 1;
    }

    FILE* file9 = fopen("../puzzlefiles/easy.txt", "r");
    puzzle_t* puzzle3 = puzzle_load(file9); 
    fclose(file9);

    if (is_puzzle_finished(puzzle3)) {
        fprintf(stderr,"Puzzle finish incorrectly for unsolved puzzle easy\n");
        return 1;
    }

    puzzle_delete(puzzle);
    puzzle_delete(puzzle2);
    puzzle_delete(puzzle3);
    return 0;
}

int main(const int argc, const char *argv[])
{
    next_unit_test(); 
    completed_next_unit();
    possibles_update_test();
    solveable_test();
    // possibles_print();
    finish_puzzle_test();
    return 0;
}
