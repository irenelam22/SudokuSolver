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
        create(fp, minshown);                       // create the puzzle
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
    if (argc < 2 || argc > 4) {				    // check number of arguments 
            fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create difficultyLevel [OPTIONAL: FILE_NAME]\nFor solve: ./sudoku solve [OPTIONAL: PUZZLE_FILE_NAME]\n\n");
            exit(1);
    }

    *command = argv[1];                                     // extract the command

    if ( strcmp(*command, "create") == 0){                  // if the command is "create"...
        if (argc < 3) {                                     // check that enough arguments were passed 
	    fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create difficultyLevel [OPTIONAL: FILE_NAME]\n");
	    exit(1); 
	}
	char *difficulty = argv[2];
	*minshown = get_minshown(difficulty); 
	if (*minshown == 0) {
	    fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create difficultyLevel [OPTIONAL: FILE_NAME]\nInput 'easy', 'medium', 'hard', or 'evil' for difficultyLevel\n");
	    exit(2); 
	}
	if (argc == 4) {
	    *file_name = argv[3];
	}
	if ( *file_name == NULL ){                          // and no file name is provided, then use standard output
            *fp = stdout; 
	    return;
        }
        *fp = fopen(*file_name, "w");                  // otherwise, try opening this file for writing
        if ( *fp == NULL ){                                  // exit if any error with this
            fprintf(stderr, "Please pass in a writable file for create.\n");
            exit(2);
        }  
    } 
    else if ( strcmp(*command, "solve") == 0){              // if the command is "solve"...
        if (argc > 3) {                                     // check that not too many arguments were passed 
	    fprintf(stderr, "Incorrect usage...\nFor solve: ./sudoku solve [OPTIONAL: PUZZLE_FILE_NAME]\n");
	    exit(1); 
	}
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
        //fclose(fp);                                         // close this test file

    } 
    else{
        fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create [OPTIONAL: FILE NAME]\nFor solve: ./sudoku solve [PUZZLE FILE NAME]\n\n");
        exit(1);
    }
}

/********get_minshown*********/
/* Calculates minimum numbers to show given the four difficulty levels
 * Where the difficulty levels have these ranges: 
 * 	Easy: 40-41, Medium: 34-39, Hard: 28-33, Evil: 22-27
*/
static int get_minshown(char* difficulty)
{
    int minshown = 0; 
    if (strcmp(difficulty, "easy") == 0) {
    	minshown = 40; 
    }
    else if (strcmp(difficulty, "medium") == 0) {
        minshown = 34; 
    }
    else if (strcmp(difficulty, "hard") == 0) {
        minshown = 28; 
    }
    else if (strcmp(difficulty, "evil") == 0) {
	minshown = 22; 
    }
    return minshown; 
}
