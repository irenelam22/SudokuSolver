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

// local function prototypes
static int generate_row_num(int unit_num);
static int generate_column_num(int unit_num);
static int generate_box_num(int row_num, int col_num);

/******* unit_new ********/
/*
 * Please refer to unit.h for function description
*/
unit_t* unit_new(int unit_num, int val){
    if ( unit_num < 1 || unit_num > 81){                // check parameters
        fprintf(stderr, "Invalid unit_num\n");
        return NULL;
    }

    if ( val < 0 || val > 9){
        fprintf(stderr, "Invalid value provided\n");
        return NULL;
    }


    unit_t* unit = malloc(sizeof(unit_t));                // allocate memory for and instantiate our unit
    unit->val = val;
    unit->unit_num = unit_num;

    int row = generate_row_num(unit_num);                // generate the unit's row number
    if ( row == -1){                                     // exit if error
        fprintf(stderr, "Error generating row_num\n");
        free(unit);
        return NULL;
    }
    unit->row_num = row;

    int col = generate_column_num(unit_num);              // generate the unit's column number
    if ( col == -1){                                      // exit if error
        fprintf(stderr, "Error generating col_num\n");
        free(unit);
        return NULL;
    }
    unit->col_num = col;

    int box = generate_box_num(col, row);               // generate the unit's box number
    if ( box == -1){                                    // exit if error
        fprintf(stderr, "Error generating box_num\n");
        free(unit);
        return NULL;
    }
    unit->box_num = box;
    unit->possibles = counters_new();                   // instantiate a counters set for the unit's possibles list

    return unit;
}

/******* generate_column_num ********/
/*
 * Local helper function to determine the column number given the unit number. We will have nine columns numbered 
 * 0-8. We will use 0-8 to make it easier to insert into our 2D array for our puzzle.
*/
static int generate_column_num(int unit_num){
    if ( unit_num < 1 || unit_num > 81){          // make sure our unit number is between 1 and 81
        fprintf(stderr, "Invalid unit_num\n");
        return -1;
    }

    int column = unit_num % 9;                     // calculate the mod to determine the given column number          
    if ( column == 0){                             // if it's in the last row...      
        column = 8;                                // assign it column number 8
    } else{
        column --;                                 // otherwise, decrement the mod to make our columns ordered 0-8
    }

    return column;
}

/******* generate_row_num ********/
/*
 * Local helper function to determine the row number given the unit number. We will have nine rows numbered 
 * 0-8. We will use 0-8 to make it easier to insert into our 2D array for our puzzle.
*/
static int generate_row_num(int unit_num){
    if ( unit_num < 1 || unit_num > 81){         // make sure our unit number is between 1 and 81
        fprintf(stderr, "Invalid unit_num\n");
        return -1;
    }

    // note: keeping column numbers 0-8 (should be easier for our 2d array)
    int row = unit_num / 9;
    if ( unit_num % 9 == 0){                    // if it's in the last column...
        row --;                                 // we need to adjust the row number calculated
    }

    return row;
}

/******* generate_box_num ********/
/*
 * Local helper function to determine the box number given the row and column numbers. We will have nine boxes numbered 
 * 1-9. Box 1 will start in the top-left corner, and then we will work our way across each row from top to bottom. 
*/
static int generate_box_num(int col_num, int row_num){
    if ( row_num < 0 || row_num > 8){                   // make sure we have a valid row number
        fprintf(stderr, "Invalid row number\n");
        return -1;
    }

    if ( col_num < 0 || col_num > 8){                   // make sure we have a valid column number
        fprintf(stderr, "Invalid column number\n");
        return -1;
    }

    // use the row and column number to designate the appropriate box
    if ( row_num < 3 && col_num < 3){                               // box 1
        return 1;
    } 
    else if ( row_num < 3 && col_num >= 3 && col_num < 6 ){         // box 2
        return 2;
    } 
    else if ( row_num < 3 && col_num >= 6 ){                        // box 3
        return 3;
    } 
    else if ( row_num >= 3 && row_num < 6 && col_num < 3){          // box 4
        return 4;
    } 
    else if ( row_num >= 3 && row_num < 6 && col_num >= 3 && col_num < 6){  // box 5
        return 5;
    } 
    else if ( row_num >= 3 && row_num < 6 && col_num >=6 ){         // box 6
        return 6;
    } 
    else if ( row_num >= 6 && col_num < 3){                         // box 7
        return 7;
    } 
    else if ( row_num >=6 && col_num >= 3 && col_num < 6 ){         // box 8
        return 8;
    } 
    else{                                                           // box 9
        return 9;
    }

    return -1;
}

/******* generate_row_num ********/
/*
 * See unit.h for description
*/
void delete_unit(unit_t* unit){
    if ( unit == NULL ){                                            // check arguments
        fprintf(stderr, "Invalid unit provided for deletion\n");
        return;
    }
    counters_delete(unit->possibles);                               // delete the possibles list
    free(unit);                                                     // clean up
    return;
}

/******* print_unit ********/
/*
 * See unit.h for description
*/
void print_unit(unit_t* unit){
    if ( unit == NULL ){                                           // check arguments
        fprintf(stderr, "Invalid unit provided for printing\n");
        return;
    }    

    // check each argument individually for error handling (note: print unit is used for debugging)

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

/******* possibles_add ********/
/*
 * See unit.h for description
*/
bool possibles_add(unit_t* unit, int val){
    if ( unit == NULL || val < 1 || val > 9){                   // check arguments
        fprintf(stderr, "Invalid inputs for possible_add\n");
        return false;
    }

    if ( counters_get(unit->possibles, val) != 0){          // if this position is already marked...
        return false;                                       // we don't need to add it again
    }

    counters_add(unit->possibles, val);                     // otherwise... mark this possibles value
    return true;
}

/******* possibles_remove********/
/*
 * See unit.h for description
*/
bool possibles_remove(unit_t* unit, int val){
    if ( val == 0) {                                        // we shouldn't have a value of zero
        return false;
    }
    if ( unit == NULL || val < 0 || val > 9){               // check arguments
        fprintf(stderr, "Invalid inputs for possible_remove\n");
        return false;
    }    
    if ( counters_get(unit->possibles, val) != 1){          // no need to "remove" if this value is not possible already
        return false;
    }

    counters_set(unit->possibles, val, 0);                  // "remove" this value from the possibles list
    return true;
}

/******* possibles_get_one_helper ********/
/*
 * Helper function for counters_iterate in possibles_get_one. 
*/
static void possibles_get_one_helper(void *arg, const int key, const int count)
{
    int* ptr = arg;
    if (*ptr == 0 && count == 1) {
        *ptr = key;
    }
}

/******* possibles_get_one ********/
/*
 * See unit.h for description
*/
int possibles_get_one(unit_t* unit) {
    if ( unit == NULL ){                                    // check arguments
        fprintf(stderr, "Invalid unit for possibles_get_one\n");
        return -1;
    }
    int ptr = 0;
    counters_t* set = unit -> possibles;
    counters_iterate(set, &ptr, possibles_get_one_helper);  // get a value from our possibles counters set
    if (ptr == 0) {                                         // reject a value of 0 
        return -1;
    }
    else {
        return ptr;
    }
}

/******* possibles_contain ********/
/*
 * See unit.h for description
*/
bool possibles_contain(unit_t* unit, int val)
{
    if ( unit == NULL || val < 1 || val > 9){               // check arguments
        return false;
    }    
    
    return counters_get(unit->possibles, val) != 0;
}

/******* possibles_isEmpty_helper ********/
/*
 * Helper function for counters_iterate in possibles_isEmpty. Note: a count of 1 in a possibles list indicates that
 * this value is a possible value. A count of 0 indicates that this value is not possible.
*/
void possibles_isEmpty_helper(void *arg, const int key, const int count){
    int* ptr = arg;
    if (ptr != NULL && count != 0) {                    // if the count in the possibles counter is not zero,
       *ptr = key;                                      // assign this value to our temp pointer (see below)
    }
}

/*******possibles_isEmpty********/
/* Checks whether the unit's possibles list is empty
 * Input: unit
 * Output: true if empty, false otherwise
 */
bool possibles_isEmpty(unit_t* unit){
    if (unit == NULL) {                                                 // check arguments
        fprintf(stderr, "possibles_isEmpty received a NULL unit\n");
        return false;
    }
    counters_t* set = unit -> possibles;
    int temp = 0;
    counters_iterate(set, &temp, possibles_isEmpty_helper);  // see possibles_isEmpty_helper       
    return temp == 0;                                        // if temp is non-zero, then there is at least one possible value
}

/*******get_unit_val********/
int get_unit_val(unit_t *unit){
    return unit->val; 
}