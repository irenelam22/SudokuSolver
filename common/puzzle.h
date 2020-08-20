#include <stdio.h>
#include <stdlib.h>
#include "unit.h"

#ifndef __PUZZLE_H
#define __PUZZLE_H

typedef unit_t **puzzle_t; 

puzzle_t* puzzle_new();  
void puzzle_print(puzzle_t *puzzle); 
puzzle_t *puzzle_load(FILE *fp); 
void puzzle_delete(puzzle_t *puzzle); 
void puzzle_iterate(puzzle_t* puzzle, void *arg, void (*itemfunc)(void *arg, unit_t* cell));
unit_t* puzzle_get_unit(puzzle_t* puzzle, int row, int col);

#endif // __PUZZLE_H 
