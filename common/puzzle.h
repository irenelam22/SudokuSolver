#include <stdio.h>
#include <stdlib.h>
#include "unit.h"


typedef unit_t **puzzle_t; 

puzzle_t* puzzle_new(); 
void puzzle_print(puzzle_t *puzzle); 
puzzle_t *puzzle_load(FILE *fp); 
void puzzle_delete(puzzle_t *puzzle); 