/* These are the 3 testing functions to see if a move is legal */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>
#include "./movechecker.h"




bool row_checker(int (*puzzle)[9], int row_num, int num );
bool column_checker(int (*puzzle)[9], int col_num, int num );
bool unit_checker(int (*puzzle)[9], int row_num, int col_num, int num);
bool valid_sudoku( int (*puzzle)[9], int size );




int main(const int argc, char *argv[]){

    int N = 9;

    int puzzle[N][N]; 

    int *puzzleptr = NULL;
    puzzleptr = &puzzle[0][0];


//generates a random sudoku 1-9 in each row 
    for(int i = 0; i < N; i++){
        for(int k =0; k< N; k++){
            puzzle[i][k] = k+1;
            puzzleptr = &puzzle[i][k];
            printf("THE PUZZLE: %d \n", *puzzleptr);
        }
    }


/* I didnt generate a valid sudoku so i played with the one i generated above and made
sure it worked for the one above */ 


    if (row_checker(puzzle, 1, 1)){
        printf("This is a valid number for the row\n");
    }else{
        printf("NAHHH BOI ILLEGAL\n");
    }

    if (column_checker(puzzle, 0, 0)){
        printf("This is a valid number for the column\n");
    }else{
        printf("NAHHH BOI SUPER ILLEGAL\n");
    }

    if(unit_checker(puzzle, 6, 6, 6)){
        printf("This is a valid number for the UNITTT \n");
    }else{
        printf("NAHHH SON YOU DONE FUCKED UP\n");
    }

    if(valid_sudoku(puzzle, 9)){
        printf("All the rows,columns, and units sum to 45\n");
    }

    return 0; 
}


bool row_checker(int (*puzzle)[9], int row_num, int num ){


    int *puzzleptr = NULL;
    puzzleptr = &puzzle[0][0];
    printf("THE PUZZLERRRR: %d \n", *(puzzleptr + 0));

    if(num > 9 || num < 1){
        fprintf(stderr, "This number is outside the scope\n");
        return false;
    }

// (*(*(puzzleptr+i)+j))
    for(int j=0; j < 3; j++){
        if( puzzle[row_num][j]  == num  ){
            return false;
        }
    }
return true;

}

bool column_checker(int (*puzzle)[9], int col_num, int num ){

if(num > 9 || num < 1){
    fprintf(stderr, "This number is outside the scope\n");
    return false;
}

int *puzzleptr = NULL;
puzzleptr = &puzzle[0][0];
printf("THE PUZZLERRRR: %d \n", *(puzzleptr + 0));

   for(int i=0; i < 3; i++){
        if( puzzle[i][col_num]  == num  ){
            return false;
        }
    }

return true;
}


bool unit_checker(int (*puzzle)[9], int row_num, int col_num, int num){

int sector_lower_col;
int sector_lower_row;
int sector_higher_col;
int sector_higher_row;

if(num > 9 || num < 1){
    fprintf(stderr, "This number is outside the scope\n");
    return false;
}
    if( (col_num < 3) && (row_num < 3) ){
        sector_lower_col = 0;
        sector_lower_row = 0;
        sector_higher_col = 3;
        sector_higher_row = 3;
        printf("YOURE IN SECTOR A \n");

    } else if( (col_num < 3) && ( 3 <= row_num ) && (row_num < 6) ){
        sector_lower_col = 0;
        sector_lower_row = 3;
        sector_higher_col = 3;
        sector_higher_row = 6;
        printf("YOURE IN SECTOR D \n");

    } else if( (col_num < 3) && ( 6 <= row_num ) && (row_num < 9) ){
        sector_lower_col = 0;
        sector_lower_row = 6;
        sector_higher_col = 3;
        sector_higher_row = 9;
        printf("YOURE IN SECTOR G \n");

    } else if( ( 3 <= col_num ) && (col_num < 6) && (row_num < 3) ){
        sector_lower_col = 3;
        sector_lower_row = 0;
        sector_higher_col = 6;
        sector_higher_row = 3;
        printf("YOURE IN SECTOR B \n");

    }  else if( ( 3 <= col_num ) && (col_num < 6) && ( 3 <= row_num ) && (row_num < 6) ){
        sector_lower_col = 3;
        sector_lower_row = 3;
        sector_higher_col = 6;
        sector_higher_row = 6;
        printf("YOURE IN SECTOR E \n");

    } else if( ( 3 <= col_num ) && (col_num < 6) && ( 6 <= row_num ) && (row_num < 9) ){
        sector_lower_col = 3;
        sector_lower_row = 6;
        sector_higher_col = 6;
        sector_higher_row = 9;
        printf("YOURE IN SECTOR H \n");

    } else if( ( 6 <= col_num ) && (col_num < 9) && (row_num < 3) ){
        sector_lower_col = 6;
        sector_lower_row = 0;
        sector_higher_col = 9;
        sector_higher_row = 3;
        printf("YOURE IN SECTOR C \n");

    } else if( ( 6 <= col_num ) && (col_num < 9) && ( 3 <= row_num ) && (row_num < 6) ){
        sector_lower_col = 6;
        sector_lower_row = 3;
        sector_higher_col = 9;
        sector_higher_row = 6;
        printf("YOURE IN SECTOR F \n");

    }  else if( ( 6 <= col_num ) && (col_num < 9) && ( 6 <= row_num ) && (row_num < 9) ){
        sector_lower_col = 6;
        sector_lower_row = 6;
        sector_higher_col = 9;
        sector_higher_row = 9;
        printf("YOURE IN SECTOR I \n");

    }else{
        printf("You have entered a row/column number that is out of bounds");
    }  

    for(int i=sector_lower_row; i < sector_higher_row; i++){
        for(int j=sector_lower_col; j < sector_higher_col; j++){
            if(puzzle[i][j] == num){
                return false;
            }
        }
    }
return true;
}



// FINAL PUZZLE CHECKER

bool valid_sudoku( int (*puzzle)[9], int size ){

    for(int i=0; i < size; i++){
        int sum = 0;
        for(int j=0; j < size; j++){
            sum = sum + puzzle[i][j];
        }
        if(sum != 45){
            fprintf(stderr, "Error row does not sum appropraitely \n");
            return false;
        }else{
            continue;
        }
    }

    for(int i=0; i < size; i++){
        int sum = 0;
        for(int j=0; j < size; j++){
            sum = sum + puzzle[j][i];
        }
        if(sum != 45){
            fprintf(stderr, "Error column does not sum appropraitely \n");
            return false;
        }else{
            continue;
        }
    }


    int sector_lower_col = 0;
    int sector_lower_row = 0;
    int sector_higher_col = 3;
    int sector_higher_row = 3;
    int sum = 0;

    while(sector_lower_row <= 6 && sector_higher_row <= 9){
        sector_lower_col = 0;
        sector_higher_col = 3;
        while(sector_lower_col <= 6 && sector_higher_col <= 9){
            sum = 0;
            for(int i=sector_lower_row; i < sector_higher_row; i++){
                for(int j=sector_lower_col; j < sector_higher_col; j++){
                    sum = sum + puzzle[i][j];
                }
            }
            if(sum != 45){
                fprintf(stderr, "Error unit does not sum appropraitely \n");
                return false;
            } 
            sector_lower_col = sector_lower_col + 3;
            sector_higher_col = sector_higher_col + 3;
        }
        sector_lower_row = sector_lower_row + 3;
        sector_higher_row = sector_higher_row + 3;
    }
    return true;
}