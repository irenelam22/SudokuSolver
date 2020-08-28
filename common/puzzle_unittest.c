/*
puzzle_unittest -- unit testing file for major puzzle methods

Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/

#include "puzzle.h"
#include "unit.h"
#include "../libcs50/memory.h"

/******* next_unit_test ********/
// Testing robustness of next_unit
int next_unit_test() 
{
    // Basic functionality test on easy.txt
    FILE* file1 = fopen("../puzzlefiles/easy.txt", "r");
    puzzle_t* puzzle = puzzle_load(file1); 
    fclose(file1);
    
    unit_t* nextUnit = next_unit(puzzle);
    nextUnit -> possibles = NULL;

    // Known answer to compare with
    unit_t ans1 = {
        .val = 0,
        .unit_num = 2,
        .row_num = 0,
        .col_num = 1,
        .box_num = 2,
    };

    // Comparing the two answers
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

    // Updating next unit test
    puzzle[nextUnit -> row_num][nextUnit -> col_num] -> val = 5;
    delete_unit(nextUnit);
    nextUnit = next_unit(puzzle);
    nextUnit -> possibles = NULL;

    // Answer to the next unit & comparison
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

/******* completed_next_unit ********/
// Testing on a completed puzzle (no next unit)
int completed_next_unit() 
{
    // Loading the file
    FILE* file2 = fopen("../puzzlefiles/easyans.txt", "r");
    puzzle_t* filled_puzzle = puzzle_load(file2); 
    fclose(file2);

    // As the puzzle is completed, there should not be a next unit
    unit_t* filled_unit = next_unit(filled_puzzle);
    if (filled_unit != NULL){
        fprintf(stderr, "Next unit on a filled puzzle failed\n");
        puzzle_delete(filled_puzzle);
        delete_unit(filled_unit);
        return 1;
    }
    
    // Clean up
    puzzle_delete(filled_puzzle);
    return 0;
}

/******* possibles_update_test ********/
// Testing whether a unit's possibles list successfully updates
int possibles_update_test()
{
    // Loading puzzle file
    FILE* file3 = fopen("../puzzlefiles/medium.txt", "r");
    puzzle_t* puzzle = puzzle_load(file3); 
    fclose(file3);

    unit_t* nextUnit = next_unit(puzzle);
    if (nextUnit == NULL) {
        fprintf(stderr, "Invalid next unit in possibles_update_test\n");
        return 1;
    }
    // Finding the correct unit
    unit_t *unit = puzzle[nextUnit -> row_num][nextUnit -> col_num];
    nextUnit -> possibles = NULL;
    counters_delete(unit -> possibles);
    delete_unit(nextUnit); 

    // Creating the possibles list and comparing with the known values
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

    // Modifying the possibles list and rechecking that the values are as expected
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

/******* solveable_test ********/
// Tests that the solveable method works (used in create)
int solveable_test()
{
    // Loading puzzle
    FILE* file5 = fopen("../puzzlefiles/badpuzzle.txt", "r");
    puzzle_t* bad_puzzle = puzzle_load(file5); 
    fclose(file5);

    // Checking validity of a bad puzzle
    if (is_puzzle_solveable(bad_puzzle)) {
        puzzle_delete(bad_puzzle);
        fprintf(stderr, "Solveable failed for badtest.txt\n");
        return 1;
    }

    // Clean up
    puzzle_delete(bad_puzzle);
    return 0;
}

/******* possibles_print ********/
/** Checking that the possibles list prints for the interface
 * As this is a printing method, manual checking was done to guarantee accuracy
 */
int possibles_print()
{
    // Load file and create possibles list
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

    // Print and manually determine accuracy
    possibles_create(puzzle, unit);
    printf("%s", possibles_print_ncurses(unit));
    puzzle_delete(puzzle);
    return 0;
}

/******* finish_puzzle_test ********/
/** Another method used specifically for the interface
 * Tests that the user has successfully completed the puzzle
 */
int finish_puzzle_test()
{
    // Loading a regular file and checking whether the puzzle is finished
    FILE* file7 = fopen("../puzzlefiles/medium.txt", "r");
    puzzle_t* puzzle = puzzle_load(file7); 
    fclose(file7);

    if (is_puzzle_finished(puzzle)) {
        fprintf(stderr,"Puzzle finish incorrectly for unsolved puzzle\n");
        return 1;
    }

    // Loading a finished file and checking whether the puzzle is finsihed
    FILE* file8 = fopen("../puzzlefiles/easyans.txt", "r");
    puzzle_t* puzzle2 = puzzle_load(file8); 
    fclose(file8);

    if (is_puzzle_finished(puzzle2)) {
        fprintf(stderr, "Puzzle finished incorrectly for answer puzzle\n");
        return 1;
    }

    // Loading another unfinished file (sanity check)
    FILE* file9 = fopen("../puzzlefiles/easy.txt", "r");
    puzzle_t* puzzle3 = puzzle_load(file9); 
    fclose(file9);

    if (is_puzzle_finished(puzzle3)) {
        fprintf(stderr,"Puzzle finish incorrectly for unsolved puzzle easy\n");
        return 1;
    }

    // Clean up
    puzzle_delete(puzzle);
    puzzle_delete(puzzle2);
    puzzle_delete(puzzle3);
    return 0;
}

/******* main ********/
// Runs the above tests (commented out print to prevent floading the terminal)
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
