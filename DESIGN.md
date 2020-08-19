# Sudoku Design Spec

Recall the [Querier Requirements Spec](REQUIREMENTS.md); the **querier** allows the user to search through the provided 
pageDirectory and index file to find keywords. The querier allows for special processing using "and" or "or" (with "and" 
have precedence). The querier will output the pages which contain the keywords (if applicable). Also, it will rank the 
pages based on how many times the word(s) appear in the given documents. 

A Design Spec should contain several sections:

* User interface
* Inputs and Outputs
* Functional decomposition into modules
* Pseudo code for logic/algorithmic flow
* Dataflow through modules
* Major data structures
* Testing plan

Let's look through each.

### User interface

#### Create
Our create program will run as follows:

```
./create [FILE_NAME]
```
Where file name is the file to which we will output our puzzle. If no puzzle name is given, we will output the puzzle to 
standard output.

#### Solve
Our solve program will run as follows:

```
./solve [PUZZLE_FILE_NAME] [SOLVED_OUTPUT]
```
* Where puzzle file name is an puzzle to be completed
* Where solved output is the completed/solved puzzle

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
* Puzzle file name: this file must be readable and must have a valid puzzle format (we will handle errors accordingly)
* Solved output file: the user has the option to input a valid, writable file to write their output to (if no file is provided here, we will output to standard output)

Outputs:
* Completed puzzle (sent to either the output file or standard output)
* Error message if invalid files provided (including invalid puzzle)

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

#### Common module function descriptions

### Dataflow through modules

#### Create

#### Solve

### Testing plan

#### Create

#### Solve

### Tests

#### Create

#### Solve
