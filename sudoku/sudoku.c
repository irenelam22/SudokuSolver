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
static void process_arguments(int argc, char* argv[], char** command, char** file_name, FILE** fp);

int main(const int argc, char *argv[]){
    char* command = NULL;                                   // should either be "create" or "solve"
    char* file_name = NULL;                                 // note: user may or may not pass a file
    //int indicator = 0;					    // equals one if file_name is stdout
    FILE *fp = NULL; 

    process_arguments(argc, argv, &command, &file_name, &fp);
    if ( strcmp(command, "create") == 0){                   // if the command is create...
        //if ( argc == 2){                                    // and the user did not provide a file name
        //    indicator = 1;                                  // then the puzzle will be sent to stdout
        //}
        create(fp);                       // create the puzzle
    }
    else if ( strcmp(command, "solve") == 0){               // if the command is solve...
	solve(fp);                                       // solve the provided puzzle
    }
    else{                                                   // if the command is not "create" or solve"...
        return 1;                                           // then there's an error
    }

    return 0;
}

static void process_arguments(int argc, char* argv[], char** command, char** file_name, FILE **fp){
    if ( argc < 2 || argc > 3){                             // expect only 2 or 3 arguments
       fprintf(stderr, "Incorrect usage...\nFor create: ./sudoku create [OPTIONAL: FILE NAME]\nFor solve: ./sudoku solve [PUZZLE FILE NAME]\n\n");
       exit(1);
    }

    *command = argv[1];                                     // extract the command
    if ( argc == 3 ){                                       // if there is a file name provided
        *file_name = argv[2];                               // extract it
    }   

    if ( strcmp(*command, "create") == 0){                  // if the command is "create"...
        if ( *file_name == NULL ){                          // and no file name is provided, then we're good to move on
            *fp = stdout; 
		return;
        }
        *fp = fopen(*file_name, "w");                  // otherwise, try opening this file for writing
        if ( *fp == NULL ){                                  // exit if any error with this
            fprintf(stderr, "Please pass in a writable file for create.\n");
            exit(2);
        }       
        //fclose(*fp);                                         // close our test file

    } 
    else if ( strcmp(*command, "solve") == 0){              // if the command is "solve"...
        if ( *file_name == NULL ){                          // and no file name is provided, then we're good to move on
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
