#include <stdio.h>
#include <stdlib.h>
#include "unit.h"

#ifndef __CREATE_H
#define __CREATE_H

void create(char* file_name, int indicator);
static bool fill_puzzle(puzzle_t *puzzle); 
static bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz, int minshown); 
static bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz); 
static void copy_puzzle(void *arg, unit_t* unit); 

#endif // __CREATE_H 