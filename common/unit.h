/* 
 * file: unit.h - header file for unit class
 * authors: David Kantor, Irene Lam
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

typedef struct unit{
    int val;
    int unit_num;
    int row_num;
    int col_num;
    int box_num;
    counters_t* possibles;
} unit_t;

unit_t* unit_new(int unit_num, int val);

void delete_unit(unit_t* unit);
void print_unit(unit_t* unit);
bool possibles_add(unit_t* unit, int val);
bool possibles_remove(unit_t* unit, int val);
bool possibles_contain(unit_t* unit, int val);
bool possibles_isEmpty(unit_t* unit);
int get_unit_val(unit_t *unit); 
int possibles_get_one(unit_t* unit);

#endif // __UNIT_H




// define unit struct
    // unit
        // value
            // int
        // row_num
            // int
        // col_num
            // int
        // box_num
            // int
        // list of possibles
            // set, hashtable, bag, counters, array, custom linked list

// functions
    // unit new 
    // print unit
    // getter methods
    // setter methods
    // delete unit
    // update possible
