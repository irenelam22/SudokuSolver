#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>


bool row_checker(int (*puzzle)[9], int row_num, int num ); //checks the row and you pass row number and number to check 

bool column_checker(int (*puzzle)[9], int col_num, int num ); //checks the column and you pass column number and number to check 

bool unit_checker(int (*puzzle)[9], int row_num, int col_num, int num); //checks the unit, pass column and row number 
//it'll determine what unit you're in and see if the number you pass is already there

bool valid_sudoku( int (*puzzle)[9], int size );
//final check for a valid sudoku puzzle, checks all the rows, columns, and units and makes sure the
//sum is 45 for each thing respectively
