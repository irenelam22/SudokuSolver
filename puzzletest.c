#include <stdio.h>
#include <stdlib.h>
#include "puzzle.h"
#include "./unit.h"

int main()
{
    puzzle_t *puzzle = puzzle_new();
    puzzle_print(puzzle);
    puzzle_delete(puzzle);

    printf("\n");

    FILE *fp = fopen("sudokuexample", "r"); 
    puzzle = puzzle_load(fp); 
    puzzle_print(puzzle); 
    puzzle_delete(puzzle); 
    fclose(fp); 

    return 0; 
}