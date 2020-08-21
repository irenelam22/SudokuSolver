#include <stdio.h>
#include <stdlib.h>
#include "unit.h"

#ifndef __PUZZLE_H
#define __PUZZLE_H

typedef unit_t **puzzle_t; 

puzzle_t* puzzle_new();  
void puzzle_print(FILE *fp, puzzle_t *puzzle); 
puzzle_t *puzzle_load(FILE *fp); 
void puzzle_delete(puzzle_t *puzzle); 
void puzzle_iterate(puzzle_t* puzzle, void *arg, void (*itemfunc)(void *arg, unit_t* cell));
unit_t* puzzle_get_unit(puzzle_t* puzzle, int row, int col);

void first_valid_unit(void* ptr, unit_t* current_cell); 
unit_t* next_unit(puzzle_t* puzzle); 
counters_t* possibles_create(puzzle_t* puzzle, unit_t* unit); 
void updating_possibles(puzzle_t* puzzle, unit_t* unit); 
void updating_possibles_helper(void *arg, unit_t* unit); 
void solveable_helper(void* ptr, unit_t* current_cell); 
bool is_puzzle_solveable(puzzle_t* puzzle); 

#endif // __PUZZLE_H 
