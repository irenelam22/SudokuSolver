/* 

file: sudoku – interface for create and solve
assignment: final project – sudoku
group: project-kidd

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../create/create.h"
#include "../solve/solve.h"

static void process_arguments(int argc, char* argv[], char** command, char** file_name);

int main(const int argc, char *argv[]){
    char* command = NULL;
    char* file_name = NULL;
    int indicator; // equals one if file_name is stdout

    process_arguments(argc, argv, &command, &file_name);
    if ( strcmp(command, "create") == 0){
        if ( argc == 2){
            indicator = 1;
        }
        create(file_name, indicator);
    }
    else if ( strcmp(command, "solve") == 0){

        solve(file_name);
    }
    else{
        return 1;
    }

    return 0;
}

static void process_arguments(int argc, char* argv[], char** command, char** file_name){
    if ( argc < 2 || argc > 3){
       fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create [OPTIONAL: FILE NAME]\nFor solve: ./sudoku solve [PUZZLE FILE NAME]\n\n");
       exit(1);
    }

    *command = argv[1];
    if ( argc == 3 ){
        *file_name = argv[2];
    }

    if ( strcmp(*command, "create") == 0){
        if ( *file_name == NULL ){
            return;
        }
        FILE* fp = fopen(*file_name, "w");
        if ( fp == NULL ){
            fprintf(stderr, "Please pass in a writable file for create.\n");
            exit(2);
        }
        fclose(fp);
        
    } 
    else if ( strcmp(*command, "solve") == 0){
        if ( *file_name == NULL ){
            return;
        }
        FILE* fp = fopen(*file_name, "r");
        if ( fp == NULL ){
            fprintf(stderr, "Please pass in a readable puzzle file for solve.\n");
            exit(3);
        }
        fclose(fp);

    } 
    else{
        fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create [OPTIONAL: FILE NAME]\nFor solve: ./sudoku solve [PUZZLE FILE NAME]\n\n");
        exit(1);
    }
}