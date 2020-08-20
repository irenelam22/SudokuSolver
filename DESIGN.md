# Sudoku Design Spec
### Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
### Dartmouth CS50, Summer 2020

**Sudoku** supports two features. The program can either create a Sudoku puzzle with a unique solution from scratch, or it takes in a puzzle and outputs a solution to the file. 

### User interface

#### Create
Our create program will run as follows:

```
./create [FILE_NAME]
```
Where file name is the file to which we will output our puzzle. If no puzzle name is given, we will output the puzzle to 
standard output.

#### Solve
The solve program's only interface with the user is on the command-line. It must always have one argument.

```
./solve PUZZLE_FILE_NAME
```
* Where `PUZZLE_FILE_NAME` refers to a puzzle-formatted file to be solved

For example 
```
./solve easy.txt
```

### Inputs and outputs

#### Create
Inputs: 
* The user has the option to input a writable file to which their puzzle will be stored.
Outputs:
* If the user does not provide a valid writable file name, output an error message
* If the user does not provide a file name, we will output to standard output
* If the user provides a file name, we will output our puzzle to the provided file
* Format:
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    ---------------------
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    ---------------------
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 
    0 0 0 | 0 0 0 | 0 0 0 

#### Solve
Inputs:
* Puzzle file name: this file must be readable formatted as a puzzle (see above)


Outputs: We load the `PUZZLE_FILE_NAME` into a puzzle data structure. In the basic sudoku puzzle, each puzzle is a 9 by 9 grid of `unit` data structures. Solve then iterates through the structure and recursively fills in numbers from 1-9 based on the rules of sudoku, backtracing to a previous unit when necessary.

The results are printed to stdout as a puzzle (see above for format).

### Major data structures

#### Unit
* Structure
* Methods

#### Puzzle
* Structure
* Methods

### Functional decomposition into modules

#### Create
##### Main
* Check arguments
* Create a new empty puzzle
* Fill the puzzle randomly
* Hide the numbers while there's still only one possible solution
* Print the completed puzzle
* Delete the puzzle/clean up

##### Main helpers
##### 

#### Solve
We anticipate the following modules or functions:

1. *main*, which parses arguments and initializes other modules
2. *solve_puzzle*, which recursively calls the following methods to fill in the missing numbers from the given puzzle (presumably incomplete)
3. *backtrace*, which deletes/cleans up the current unit and returns a pointer to the previous modifiable pointer (if any)
4. *possibles_create*, which creates a new list of possibles based on values in the row, column,and box
5. *possibles_isEmpty*, which checks whether there is a possible number that can be inserted at a particular unit
6. *possibles_get_one*, which returns a possible number from the unit's possibles list
7. *possibles_remove*, which removes the possiblity from the list upon failure
5. *updating_possibles*, which updates a given unit's list of possibles based on values in the row, column and box (helper to possibles_create)
6. *is_puzzle_solveable*, which checks whether a puzzle has a solution at any given iteration
7. *next_unit*, which returns the next unit to be filled within the puzzle

And a helper module that provides data structures:

 1. *counterset* to keep track of the list of possible numbers for each unit

Additionally, we introduce the below local data types:
 1. *unit*, which stores the value, row number, column number, box number, unit number, and possibles list
 2. *puzzle*, which organizes all of the unit data structures into a 2D array

 Please see the *Major Data Structures* section for more details regarding these data structures.

#### Common module function descriptions

### Dataflow through modules

#### Create

#### Solve
1. *main* parses arguments, validates them, loads the puzzle, and passes them to *solve_puzzle*
2. *solve_puzzle* recursively solves the given puzzle by finding the next unit using *next_unit*, iterating through or updating the possibles list, and inserting/backtracing accordingly
3. *next_unit* finds the next unit to be filled within the puzzle
4. *possibles_create* creates a new list of possibles if necessary, discluding the values in the row, column,and box from the unit's possibles list
5. *possibles_isEmpty* checks whether there is a possible number that can be inserted at a particular unit
6. *possibles_get_one* returns a possible number from the unit's possibles list
7. *possibles_remove* removes the possiblity from the list upon failure

### Pseudo code for logic/algorithmic flow

### Create

### Solve
The solve portion of Sudoku will run as follows:

```c
1. Execute from a command line with usage syntax `./solve PUZZLE_FILE_NAME`
2. Validate its command-line arguments:
    1. Ensure `PUZZLE_FILE_NAME` is the pathname for an existing readable file, formatted as a puzzle
3. Load the index from `PUZZLE_FILE_NAME` into an internal puzzle data structure.
4. Solve the puzzle recursively.
    1. Retrieve the next fillable unit within the puzzle
    2. Until the next unit is not NULL, continue (as NULL indicates that the puzzle is solved)
    3. Create a possibles list for this unit
    4. If there are no possible numbers to input in this unit (i.e. possibls is empty)
        1. Delete the possibles list
        2. Set the value of the unit to the empty-cell value
        3. Return false as there is no solution using the current puzzle values
    5. For each possible number, p, in the unit
        1. Set the unit value to be p
        2. Solve the puzzle with the newly changed puzzle and return true if solveable
        3. Otherwise, remove the value from the list of possibles as it did not result in a solveable solution
5. Clean up and return false as there is no solution to the puzzle
```

### Testing plan

#### Create

#### Solve

### Tests

#### Create

#### Solve
