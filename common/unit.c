/* 

file: unit.c – implementation for unit class
assignment: final project – sudoku
group: project-kidd

*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./unit.h"
#include "../libcs50/counters.h"

// local functions
static int generate_row_num(int unit_num);
static int generate_column_num(int unit_num);
static int generate_box_num(int row_num, int col_num);

unit_t* unit_new(int unit_num, int val)
{
    if ( unit_num < 1 || unit_num > 81){
        fprintf(stderr, "Invalid unit_num\n");
        return NULL;
    }

    if ( val < 0 || val > 9){
        fprintf(stderr, "Invalid value provided\n");
        return NULL;
    }


    unit_t* unit = malloc(sizeof(unit_t));
    unit->val = val;
    unit->unit_num = unit_num;

    int row = generate_row_num(unit_num);
    if ( row == -1){
        fprintf(stderr, "Error generating row_num\n");
        free(unit);
        return NULL;
    }
    unit->row_num = row;

    int col = generate_column_num(unit_num);
    if ( col == -1){
        fprintf(stderr, "Error generating col_num\n");
        free(unit);
        return NULL;
    }
    unit->col_num = col;

    int box = generate_box_num(col, row);
    if ( box == -1){
        fprintf(stderr, "Error generating box_num\n");
        free(unit);
        return NULL;
    }
    unit->box_num = box;
    unit->possibles = counters_new();

    return unit;
}

static int generate_column_num(int unit_num)
{
    if ( unit_num < 1 || unit_num > 81){
        fprintf(stderr, "Invalid unit_num\n");
        return -1;
    }

    // note: keeping row numbers 0-8 (should be easier for our 2d array)
    int mod = unit_num % 9;
    if ( mod == 0){
        mod = 8;
    } else{
        mod --;
    }

    return mod;
}

static int generate_row_num(int unit_num)
{
    if ( unit_num < 1 || unit_num > 81){
        fprintf(stderr, "Invalid unit_num\n");
        return -1;
    }

    // note: keeping column numbers 0-8 (should be easier for our 2d array)
    int mod = unit_num / 9;
    if ( unit_num % 9 == 0){
        mod --;
    }

    return mod;
}

static int generate_box_num(int col_num, int row_num)
{
    if ( row_num < 0 || row_num > 8){
        fprintf(stderr, "Invalid row number\n");
        return -1;
    }

    if ( col_num < 0 || col_num > 8){
        fprintf(stderr, "Invalid column number\n");
        return -1;
    }

    // use the row and column number to designate the appropriate box
    if ( row_num < 3 && col_num < 3){
        return 1;
    } else if ( row_num < 3 && col_num >= 3 && col_num < 6 ){
        return 2;
    } else if ( row_num < 3 && col_num >= 6 ){
        return 3;
    } else if ( row_num >= 3 && row_num < 6 && col_num < 3){
        return 4;
    } else if ( row_num >= 3 && row_num < 6 && col_num >= 3 && col_num < 6){
        return 5;
    } else if ( row_num >= 3 && row_num < 6 && col_num >=6 ){
        return 6;
    } else if ( row_num >= 6 && col_num < 3){
        return 7;
    } else if ( row_num >=6 && col_num >= 3 && col_num < 6 ){
        return 8;
    } else{
        return 9;
    }

    return -1;
}

void delete_unit(unit_t* unit)
{
    if ( unit == NULL ){
        fprintf(stderr, "Invalid unit provided for deletion\n");
        return;
    }
    counters_delete(unit->possibles);
    free(unit);
    return;
}

void print_unit(unit_t* unit)
{
    if ( unit == NULL ){
        fprintf(stderr, "Invalid unit provided for printing\n");
        return;
    }    

    if ( unit->val < 0){
        fprintf(stderr, "Invalid unit value\n");
        return;
    }

    if ( unit->unit_num < 0){
        fprintf(stderr, "Invalid unit_num\n");
        return;
    }

    if ( unit->row_num < 0){
        fprintf(stderr, "Invalid row number\n");
        return;
    } 

    if ( unit->col_num < 0){
        fprintf(stderr, "Invalid column number\n");
        return;
    }   

    if ( unit->box_num < 0){
        fprintf(stderr, "Invalid box number\n");
        return;
    }  

    if ( unit->possibles == NULL ){
        fprintf(stderr, "Invalid possibles list\n");
        return;
    }  

    printf("\n\nValue: %d\nUnit_num: %d\nRow Number: %d\nColumn Number: %d\nBox Number: %d\n\n", unit->val, unit->unit_num,
    unit->row_num, unit->col_num, unit->box_num);
    printf("Possibles list: ");
    counters_print(unit->possibles, stdout);

}

bool possibles_add(unit_t* unit, int val)
{
    if ( unit == NULL || val < 1 || val > 9){
        fprintf(stderr, "Invalid inputs for possible_add\n");
        return false;
    }

    if ( counters_get(unit->possibles, val) != 0){
        return false;
    }

    counters_add(unit->possibles, val);
    return true;
}

bool possibles_remove(unit_t* unit, int val)
{
    if ( unit == NULL || val < 1 || val > 9){
        fprintf(stderr, "Invalid inputs for possible_remove\n");
        return false;
    }    

    if ( counters_get(unit->possibles, val) != 1){
        return false;
    }

    counters_set(unit->possibles, val, 0);
    return true;
}

int possibles_get_one(unit_t* unit) 
{
    int* ptr = NULL;
    counters_t* set = unit -> possibles;
    counters_iterate(set, ptr, possibles_get_one_helper);
    if (ptr == NULL) {
        return -1;
    }
    else {
        return *ptr;
    }
}

void possibles_get_one_helper(void *arg, const int key, const int count)
{
    if (arg != NULL && count == 1) {
        arg = key;
    }
}

bool possibles_contain(unit_t* unit, int val)
{
    if ( unit == NULL || val < 1 || val > 9){
        fprintf(stderr, "Invalid inputs for possibles_contain\n");
        return false;
    }    

    if ( counters_get(unit->possibles, val) != 0){
        return true;
    } else{
        return false;
    }
}

void possibles_isEmpty_helper(void *arg, const int key, const int count)
{
    if (arg != NULL && count != 0) {
        arg = key;
    }
}

/*******possibles_isEmpty********/
/* Checks whether the unit's possibles list is empty
 * Input: unit
 * Output: true if empty, false otherwise
 */
bool possibles_isEmpty(unit_t* unit)
{
    if (unit == NULL) {
        fprintf(stderr, "possibles_isEmpty received a NULL unit");
        return false;
    }
    counters_t* set = unit -> possibles;
    char* temp = NULL;
    counters_iterate(set, temp, possibles_isEmpty_helper);
    return temp == NULL;
}

/*******get_unit_val********/
int get_unit_val(unit_t *unit)
{
    return unit->val; 
}