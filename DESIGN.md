# Sudoku Design Spec
### Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
### Dartmouth CS50, Summer 2020
 
**Sudoku** supports two features. The program can either create a Sudoku puzzle with a unique solution from scratch, or it can take in a puzzle and output a solution. Rules of sudoku: (1) each row will contain the values 1-9 (no duplicates), (2) each column will contain the values 1-9 (no duplicates), and  (3) each box (3x3 grid) will contain the values 1-9 (no duplicates). 

</br>
Please note: In our puzzles, the boxes are separated by dashed lines (see below).
 
 
### User interface
 
Our program will have two options: create and solve

* The create option will run as follows:

```c
./sudoku create [OPTIONAL: DIFFICULTY LEVEL]
```
Where file name is the file to which we will output our puzzle. If no puzzle name is given, we will output the puzzle to
standard output.


* The solve option will run as follows:

```c
./sudoku solve [OPTIONAL: PUZZLE_FILE_NAME]
```
Where `PUZZLE_FILE_NAME` refers to a puzzle-formatted file to be solved.
 
For example
```
./sudoku solve easy.txt
```
or 

```
./sudoku solve < easy.txt
```

 
### Inputs and outputs
 
#### Create
Inputs:
* The user has the option to select a difficulty level which will determine the number of values showed</br>

Outputs:
* If the user does not provide a difficulty level of "easy," "medium," or "hard," output an error message
* We will output the puzzle to standard output
* Puzzle format:
```
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
```
 
#### Solve
Inputs:
* (Optional) Puzzle file name: this file must be readable and formatted as a puzzle (see above)
 
Outputs: 
* Error message if invalid arguments
* Otherwise, the completed puzzle is printed to stdout (see the format above)
 
Note: We load the `PUZZLE_FILE_NAME` into a puzzle data structure. In the basic sudoku puzzle, each puzzle is a 9 by 9 grid of `unit` data structures. Solve then iterates through the structure and recursively fills in numbers from 1-9 based on the rules of sudoku, backtracing to a previous unit when necessary.
 
 
### Major data structures
 
#### Unit
* Structure</br>
Each unit will have access to its *row number* (0-8), *column number* (0-8), *box number* (1-9), *unit number* (1-81), *value* (1-9), and *list of possible values*. 
</br></br>For example, the unit with a unit number of 10 will be located in row 1, column 0, box 1, will have some value 1-9, and will have a list of possible numbers for that position. We are using 0-8 for row and column numbers to make it easier to loop through our 2d puzzle array. I will denote this example unit as "x" below

```
Columns --> 
Rows
|
|
V     0 0 0 | 0 0 0 | 0 0 0
      x 0 0 | 0 0 0 | 0 0 0
      0 0 0 | 0 0 0 | 0 0 0
      ---------------------
      0 0 0 | 0 0 0 | 0 0 0
      0 0 0 | 0 0 0 | 0 0 0
      0 0 0 | 0 0 0 | 0 0 0
      ---------------------
      0 0 0 | 0 0 0 | 0 0 0
      0 0 0 | 0 0 0 | 0 0 0
      0 0 0 | 0 0 0 | 0 0 0
```

* Methods
	* *unit_new*: instantiates a new unit and generates the row, column, and box number for the provided unit number
	* *generate_col_num*: generates the column number for the given unit
	* *generate_row_num*: generates the row number for the given unit
	* *generate_box_num*: generates the unit number for the given unit
	* *delete_unit*: deletes the provided unit and clears the memory allocated for it
	* *print_unit*: display all elements of the unit (for debugging purposes)
	* *possibles_add*: add a number (1-9) to the list of possible values for this unit
	* *possibles_remove*: remove a number (1-9) from the list of possible values for this unit
	* *possibles_contain*: determine if this unit’s possible values list contains the provided value
	* *get_unit_val*: return the unit’s unit value (1-81)
 
 
#### Puzzle
* Structure: `puzzle` is a 2D array of unit structs, used to store information about the entire sudoku puzzle as it’s being created and solved
* Methods: 
	* *puzzle_new*: creates new empty puzzle, where the value of each unit is 0
	* *puzzle_print*: prints a given puzzle struct to a given file pointer 
	* *puzzle_load*: loads in a puzzle struct from a given file pointer; returns NULL if file is not properly formatted 
	* *puzzle_get_unit*: returns the unit in a given row and column number in a puzzle
	* *puzzle_iterate*: allows the user to call a given itemfunc using a given arg on every unit in a puzzle 
	* *puzzle_delete*: frees all allocated memory for a given puzzle
* Additional methods, for creating/solving functionality: 
   * *possibles_create*, which creates a new list of possibles based on values in the row, column,and box
   * *possibles_isEmpty*, which checks whether there is a possible number that can be inserted at a particular unit
   * *possibles_get_one*, which returns a possible number from the unit's possibles list
   * *possibles_remove*, which removes the possiblity from the list upon failure
   * *updating_possibles*, which updates a given unit's list of possibles based on values in the row, column and box (helper to possibles_create)
   * *is_puzzle_solveable*, which checks whether a puzzle has a solution at any given iteration
   * *next_unit*, which returns the next unit to be filled within the puzzle
 
### Functional decomposition into modules
 
#### Create
We anticipate the following modules or functions:

1. *main*, which parses arguments, initializes modules, and calls create functionality  
2. *fill_puzzle*, which randomly adds numbers into the puzzle, making sure the puzzle still follows the rules of sudoku, until the puzzle is full 
3. *get_random_possible*, which finds a random number from a given unit's set of possibles 
4. *has_one_solution*, which tests to see if a given puzzle has only one unique solution 
5. *hide_nums*, which randomly selects values to remove from given puzzle while there’s still only one solution to the puzzle 
 
Additionally, we introduce the below local data types:
1. *unit*, which stores the value, row number, column number, box number, unit number, and possibles list
   * where the possibles list is implemented with a *counterset*, to keep track of the list of possible numbers for each unit
2. *puzzle*, which organizes all of the unit data structures into a 2D array
 
Please see the *Major Data Structures* section for more details regarding these data structures. 
 
#### Solve

We anticipate the following modules or functions:
 
1. *main*, which parses arguments and initializes other modules
2. *solve_puzzle*, which recursively calls the following methods to fill in the missing numbers from the given puzzle (presumably incomplete)
3. *backtrace*, which deletes/cleans up the current unit and returns a pointer to the previous modifiable pointer (if any)
 
And solve will also rely on *unit*, *puzzle*, and *counterset*, as described above in create, and in the *Major Data Structures* section. 
 
 
### Dataflow through modules
 
#### Create
1. *main* checks arguments, creates a new empty puzzle, calls *fill_puzzle* to create a full puzzle, call *hide_nums* to remove numbers while there's still only one solution, prints the puzzle, then cleans up memory 
2. *fill_puzzle* iterates through each empty element in the puzzle using *next_unit*, then calling *get_random_possible* to temporarily store random numbers in each box, and inserting/backtracing accordingly 
3. *get_random_possible* randomly generates numbers 1-9, and returns the first one that is in the given unit's set of possibles 
4. *hide_nums* randomly generates row/column numbers to remove numbers in the puzzle, calling *has_one_solution* to make sure the puzzle has one unique solution
5. *has_one_solution* takes an incomplete puzzle and a complete puzzle, calls *fill_puzzle* to randomly fill the incomplete puzzle, then compares it to the complete puzzle to see if they got the same result

 
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
The create portion of Sudoku will run as follows: 
1. Execute from a command line with the usage syntax `./sudoku create [OPTIONAL: DIFFICULTY LEVEL]`
2. Validate its command-line arguments: 
   * If a difficulty level is provided, make sure it is "easy," "medium," or "hard"
3. Create an empty puzzle 
4. Fill the puzzle randomly, using recursion
   * Same process as the pseudocode described below in Solve under #4, except *fill_puzzle* gets random numbers from the possibles list
5. Store the full puzzle in another puzzle struct, for later comparison with *has_one_solution*
6. Hide numbers in the puzzle randomly one by one until we reach the max numbers to be shown
7. Next, remove numbers while there's still our best estimate of one unique solution, and while above the min numbers to be shown
8. Once we're done removing numbers, check if we are still within the correct interval of numbers to show -- if not, go back to the full puzzle and repeat the removing numbers process until we have a good puzzle
9. Print the puzzle to the given file, or if none given, to standard output
10. Clean up memory 
 
### Solve
The solve portion of Sudoku will run as follows:
 
1. Execute from a command line with usage syntax `./sudoku solve [OPTIONAL: PUZZLE_FILE_NAME]`
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

 
 
 
### Testing plan
From a high level, we should be able to test our creator and solver pretty easily by creating a few puzzles and passing them into our solver to see if we get completed puzzles as the output. Of course, we will want to test each piece individually, as well, and we will want to do thorough error checking. We can also create a fuzzy testing file which randomly generates a few puzzles and passes them into our solver to make sure that it works properly. 

##### Unit Testing
We will test some of the individual functions in puzzle solve and create. </br> </br>
Examples: 
* Once we have a completed puzzle, before we “hide” some of the values, we will scan through each element of the puzzle to make sure it satisfies the sudoku requirements. If our puzzle is valid, then we will move forward. 
* Check if possibles list is updating correctly
* Check if puzzle is inserting numbers correctly
* Check if backtracking is working


#### Create
##### Error Checking
* Incorrect number of arguments
* Invalid arguments
   * Non-writable file
 
#### Solve
##### Error checking
* Incorrect number of arguments
* Invalid arguments
   * Empty file
   * Non-readable file
* Pass in an invalid puzzle
   * Row, column, and/or box violations with given numbers
   Example: 
```
   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 2 2 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0
   ---------------------
   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0
   ---------------------
   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0

```
* Puzzle with incorrect formatting
```

   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0
   ---------------------
   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0
   0 0 0 | 0 0 0 | 0 0 0
   ---------------------
   0 0 0 | 0 0 0 | 0 0 0

 ```

 
 

