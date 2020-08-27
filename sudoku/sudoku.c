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
#include "../libcs50/memory.h"

// local function prototypes
static int get_minshown(char *difficulty); 
static void process_arguments(int argc, char* argv[], char** command, char** file_name, FILE** fp, int *minshown);

int main(const int argc, char *argv[]){
    char* command = NULL;                                   // should either be "create" or "solve"
    char* file_name = NULL;                                 // note: user may or may not pass a file
    FILE *fp = NULL; 
    int minshown; 

    process_arguments(argc, argv, &command, &file_name, &fp, &minshown);
    if ( strcmp(command, "create") == 0){                   // if the command is create...
        create(stdout, minshown);                       // create the puzzle
    }
    else if ( strcmp(command, "solve") == 0){               // if the command is solve...
	solve(fp);                                       // solve the provided puzzle
    }
    else{                                                   // if the command is not "create" or solve"...
        return 1;                                           // then there's an error
    }

    return 0;
}

static void process_arguments(int argc, char* argv[], char** command, char** file_name, FILE **fp, int *minshown){
    if (argc < 2 || argc > 3) {				    // check number of arguments 
            fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create [OPTIONAL: difficultyLevel]\nFor solve: ./sudoku solve [OPTIONAL: PUZZLE_FILE_NAME]\n\n");
            exit(1);
    }

    *command = argv[1];                                     // extract the command

    if ( strcmp(*command, "create") == 0){                  // if the command is "create"...
        char *difficulty; 
	if (argc == 3) {				    // if difficulty level provided, read that in
	    difficulty = argv[2];
	}
	else {
	    difficulty = "medium";			    // if no difficulty level provided, default to medium
	}
	*minshown = get_minshown(difficulty);
	if (*minshown == 0) {
	    fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create [OPTIONAL: difficultyLevel]\nInput 'easy', 'medium', or 'hard' for difficultyLevel\n");
	    exit(2); 
	} 
    } 
    else if ( strcmp(*command, "solve") == 0){              // if the command is "solve"...
	if (argc == 3) {
	    *file_name = argv[2];
	}
	if ( *file_name == NULL ){                          // and no file name is provided, then use standard input
             *fp = stdin; 
		return;
        }
        *fp = fopen(*file_name, "r");                  // otherwise, try to open this file for reading
        if ( *fp == NULL ){                                  // exit if error
            fprintf(stderr, "Please pass in a readable puzzle file for solve.\n");
            exit(3);
        }
    } 
    else{
        fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create [OPTIONAL: difficultyLevel]\nFor solve: ./sudoku solve [PUZZLE FILE NAME]\n\n");
        exit(1);
    }
}

/********get_minshown*********/
/* Calculates minimum numbers to show given the four difficulty levels
 * Where the difficulty levels have these ranges: 
 * 	Easy: 39-41, Medium: 33-38, Hard: 27-32
*/
static int get_minshown(char* difficulty)
{
    int minshown = 0; 
    if (strcmp(difficulty, "easy") == 0) {
    	minshown = 39; 
    }
    else if (strcmp(difficulty, "medium") == 0) {
        minshown = 33; 
    }
    else if (strcmp(difficulty, "hard") == 0) {
        minshown = 27; 
    }
    return minshown; 
}
