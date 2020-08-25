/*

create.h -- header file for creating the sudoku puzzle

The create program will be called by our sudoku program 
to create a new sudoku puzzle. The user will have the option either to provide
a file to which the output will be sent, or to provide no file name (the output 
will be sent to stdout)

Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
Dartmouth CS50, Summer 2020
*/
#include <stdio.h>
#include <stdlib.h>
#include "unit.h"

#ifndef __CREATE_H
#define __CREATE_H

/******** create *********/
/*
Creates a random sudoku puzzle
Inputs:
- file_name (if any) to print the sudoku puzzle to
- indicator to represent whether a filename was given
Output: none (prints to the given file/stdout)
*/
void create(char* file_name, int indicator);

/********gen_random_num*********/
/* random number generator, used because 
*  rand() wasn't producing random enough numbers
* 
*  code inspired by cs.yale.edu
*/
unsigned int gen_random_num(int min, int max);

/*********get_random_possible**********/
/* get random number from the unit's possibles 
*/
int get_random_possible(unit_t *unit);

static bool fill_puzzle(puzzle_t *puzzle); 
static bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz, int minshown); 
static bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz); 
static void copy_puzzle(void *arg, unit_t* unit); 

#endif // __CREATE_H 