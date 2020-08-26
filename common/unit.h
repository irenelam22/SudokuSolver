/* 
 * file: unit.h - header file for unit class
 * authors: David Kantor, Irene Lam, David Perez Gonzalez, Kelly Westkaemper
 * 
 *  A "unit" represents one "input" of our sudoku puzzle. The unit_t struct will contain the unit's row number,
 * column number, box number, value, unit number (x of 81 for 9x9 grid), and list of possible values. 
 *
 * CS50 
 */



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../libcs50/counters.h"

#ifndef __UNIT_H
#define __UNIT_H

/**************** global types ****************/
typedef struct unit{
    int val;
    int unit_num;
    int row_num;
    int col_num;
    int box_num;
    bool is_original;
    counters_t* possibles;
} unit_t;

/**************** functions ****************/
/**************** unit_new ****************/
/* Instantiate a new unit
 * 
 * Caller provides:
 *   a unit number
 * We return:
 *   a unit item with the row number, column number, and box number automatically generated
 * We do:
 *  ignore if unit_num or the value is out of the bounds
 *  instantiate a new unit item
 *  generate and fill in the row, column, and box numbers
 *  create a new possibles counters set
 *  return the unit
 */
unit_t* unit_new(int unit_num, int val);

/**************** delete_unit ****************/
/* Delete and free the memory for a given unit
 * 
 * Caller provides:
 *   a unit item
 * We return:
 *   nothing
 * We do:
 *  ignore if unit is NULL
 *  free the memory for/delete the possibles list
 *  free the memory for the unit itself
 * 
 */
void delete_unit(unit_t* unit);

/**************** print_unit ****************/
/* Prints the contents of a given unit
 * 
 * Caller provides:
 *   a unit item
 * We return:
 *   nothing
 * We do:
 *  ignore if unit is NULL
 *  print which element(s) within our unit are invalid
 *  print each element of the given unit
 * 
 */
void print_unit(unit_t* unit);

/**************** possibles_add ****************/
/* Marks the given value as a possible value in our possibles list
 * 
 * Caller provides:
 *   a unit item and a value
 * We return:
 *   true if successfully added
 *   false if not successfully added
 * We do:
 *  ignore if unit is NULL or if value is out of bounds
 *  check if this value is already marked as possible (exit if so)
 *  increment the counter for this given value (marking it as possible)
 * 
 */
bool possibles_add(unit_t* unit, int val);

/**************** possibles_remove ****************/
/* Marks the given value as not possible in our possibles list
 * 
 * Caller provides:
 *   a unit item and a value
 * We return:
 *   true if successfully removed
 *   false if not successfully removed
 * We do:
 *  ignore if unit is NULL or if value is out of bounds
 *  check if this value is already marked as not possible (exit if so)
 *  decrement the counter for this given value (marking it as not possible)
 * 
 */
bool possibles_remove(unit_t* unit, int val);

/**************** possibles_contain ****************/
/* Determines if the given value is a possible value
 * 
 * Caller provides:
 *   a unit item and a value
 * We return:
 *   true if it is a possible value
 *   false if not a possibe value
 * We do:
 *  ignore if unit is NULL or if value is out of bounds
 *  check if the counter for the given value is not zero
 *  if it's not zero, then it is a possible value 
 * 
 */
bool possibles_contain(unit_t* unit, int val);

/**************** possibles_isEmpty ****************/
/* Determines if there are no more possible values
 * 
 * Caller provides:
 *   a unit item
 * We return:
 *   true if empty
 *   false if not empty
 * We do:
 *  ignore if unit is NULL
 *  loop over our possibles list
 *  if any number is possible (counter == 1), then our possibles is not empty
 * 
 */
bool possibles_isEmpty(unit_t* unit);

/**************** get_unit_val ****************/
/* Returns the unit's value
 * 
 * Caller provides:
 *   a unit item
 * We return:
 *   the unit's current value
 * We do:
 *  ignore if unit is NULL 
 *  return the unit's value
 * 
 */
int get_unit_val(unit_t *unit); 

/**************** possibles_get_one ****************/
/* Fetches a possible value from our possibles list
 * 
 * Caller provides:
 *   a unit item
 * We return:
 *   the fetched value if there are any possible values
 *   -1 if there are no possible values
 * We do:
 *  ignore if unit is NULL
 *  loop over our possibles list until we find a possible value
 *  return that value (if one is found)
 * 
 */
int possibles_get_one(unit_t* unit);

char* possibles_print_ncurses(unit_t* unit);

#endif // __UNIT_H
