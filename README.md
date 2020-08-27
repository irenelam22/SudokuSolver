# CS50 Sudoku Final Project
### Team KIDD -- Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez

## Sudoku
Our project supports two features: generating a new 9x9 puzzle, or solving a given 9x9 puzzle. For the latter, the program takes in a puzzle-formatted file and prints to stdout the solution, if any. It also allows you to specify difficulty level: easy, medium, or hard, where the number of shown boxes for each difficulty level are: 
* Easy: 39-41
* Medium: 33-38
* Hard: 27-32 (**note**: sudoku can take a while longer to create a 'hard' puzzle)
When no difficulty level is provided, sudoku defaults to the 'medium' difficulty. 

Rules of sudoku: 
(1) each row will contain the values 1-9 (no duplicates), 
(2) each column will contain the values 1-9 (no duplicates), and  
(3) each box (3x3 grid) will contain the values 1-9 (no duplicates). 

Additionally, our sudoku is formatted like so: 
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

### create
`create` randomly generates an unsolved puzzle with at least 40 missing numbers. To do so, it first creates an empty puzzle, then recursively fills all units in the puzzle, making sure the rules of sudoku are held. Then, it begins randomly removing numbers from the puzzle, until we are in the specified range for the given difficulty level (as described above), **and** there is our best approximation (\*) of one unique solution. Once it's done removing numbers, create prints the unfinished puzzle to standard output. 
<br/>
\* "Best approximation" - while our puzzle cannot guarantee with 100% confidence that the created puzzle has only one unique solution, we approximate that there's one unique solution by randomly solving the puzzle and comparing it to the original solution. If the two completed puzzles match, i.e. the randomly solved puzzle is the actual solution, then we determine that that solution is likely the one unique solution to the puzzle. However, there is a small chance that another random solution could be generated. 
* However, we have a pseudo-proof of a possible way to guarantee uniqueness using Group Theory: see the section "Pseudo proof of uniqueness" below. We did not implement this solution because we determined that the math would be too complicated (as it is a NP-hard problem).  

### solve

`solve` takes in a (presumably) unsolved puzzle and recursively populates each unit in the puzzle. In particular, each unit maintains a set of possible values (of which discludes values from the unit's row, column, and block). While this set is populated, the program attempts to insert one of these values into the puzzle, and backtraces to a previous unit if no such possible values exist. Solve continues this process until the entire puzzle is populated.

### Jargon used 
Here are the common terms we use to discuss our sudoku, in both our documentation and our code: 
* `puzzle`: the entire sudoku puzzle itself
* `box`: one of the 9 3x3 grids in the puzzle
* `unit`: an individual cell within a sudoku puzzle (for instance, there are 81 units in a puzzle)


### Usage

The *sudoku* module, supporting solving and creating a puzzle, implemented in `solve.c` and `create.c` respectively, interacts with the user's commands using the following methods:

#### Unit module
```c
typedef unit_t;

unit_t* unit_new(int unit_num, int val);

void delete_unit(unit_t* unit);
void print_unit(unit_t* unit);
bool possibles_add(unit_t* unit, int val);
bool possibles_remove(unit_t* unit, int val);
bool possibles_contain(unit_t* unit, int val);
bool possibles_isEmpty(unit_t* unit);
int get_unit_val(unit_t *unit); 
int possibles_get_one(unit_t* unit);
```

#### Puzzle module
```c
typedef unit_t **puzzle_t; 

puzzle_t* puzzle_new();  
void puzzle_print(FILE *fp, puzzle_t *puzzle); 
puzzle_t *puzzle_load(FILE *fp); 
void puzzle_delete(puzzle_t *puzzle); 
void puzzle_iterate(puzzle_t* puzzle, void *arg, void (*itemfunc)(void *arg, unit_t* cell));
unit_t* puzzle_get_unit(puzzle_t* puzzle, int row, int col);

void first_valid_unit(void* ptr, unit_t* current_cell); 
unit_t* next_unit(puzzle_t* puzzle); 
counters_t* possibles_create(puzzle_t* puzzle, unit_t* unit); 
void updating_possibles(puzzle_t* puzzle, unit_t* unit); 
void updating_possibles_helper(void *arg, unit_t* unit); 
void solveable_helper(void* ptr, unit_t* current_cell); 
bool is_puzzle_solveable(puzzle_t* puzzle); 
void valid_populate_helper(void *arg, unit_t* cell);
void valid_check_helper(void *arg, unit_t* cell);
bool is_puzzle_finished(puzzle_t* puzzle);
```

### Create module
```c
void create(char* file_name, int indicator);
bool fill_puzzle(puzzle_t *puzzle); 
bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz, int minshown); 
int remove_random_num(puzzle_t *puzzle, int *numshown, int *row, int *col);
bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz); 
void copy_puzzle(void *arg, unit_t* unit); 
```

#### Solve module
```c
void solve(char* file_name);
bool solve_puzzle(puzzle_t* puzzle);
```

Please run the following to execute `sudoku`:
`./sudoku create [difficultyLevel]` to create a 9x9 puzzle
* where `difficultyLevel` is an optional parameter specifying the range of numbers to be shown, as described above
* if no `difficultyLevel` is given, create defaults to `medium`, which shows 33-38 numbers

`./sudoku solve [FILE_NAME]` to solve a 9x9 puzzle
* where `FILE_NAME` is an optional parameter specifying pathname of a puzzle-formatted file, presumably created by sudoku create
* If no `FILE_NAME` is given, solve reads from standard input 

### Implementation

Please refer to `IMPLEMENTATION.md` for details regarding implementation.

### Assumptions

We made the same assumptions as those listed within the specs of this assignment, as well as those listed within this file. 

Additionally, we assumed that it is largely not possible to determine a unique solution given the requirements of this assignment (that at least 40 missing numbers are present in the generated puzzle). Please see our corresponding pseudo-proof for our reasoning behind this.

### Pseudo-proof of uniqueness
In `Proof_Sudoku_Solutions.pdf`, we show an example of how one could implement a sudoku algorithm that guarantees uniqueness for created puzzles using Group Theory. However, in general, this is a NP-hard problem where uniqueness is guaranteed only in defined circumstances based on automorphic and symmetric grouping. As such, our sudoku creation algorithm attempts to generate a close to a unique puzzle as possible (this accuracy will deviate based on the difficult levels).  

### Files/directories

Files in main `project-kidd` directory: 
* `Makefile` - compilation procedure
* `IMPLEMENTATION.md` - implementation details 
* `DESIGN.md` - design specs 
* `Proof_sudoku_solutions.pdf` - our pseudo-proof showing how one could generate sudokus guaranteeing a unique solution using group theory

Other directories/files: 
* `common`: 
    * `unit.h/unit.c` - header and implementation of unit module
    * `puzzle.h/puzzle.c` - header and implementation of puzzle module
    * `movechecker.h/movechecker.c` - header and implementation of puzzle checking functionality 
    * `Makefile` - compilation 
* `libcs50`: CS 50 provided code
* `create`: 
    * `create.h/create.c` - header and implementation of create functionality
    * `Makefile` - compliation 
* `solve`
    * `solve.h/solve.c` - header and implementation of solve functionality
    * `Makefile` - compliation
* `sudoku`
    * `sudoku.c` - actual sudoku functionality
    * `Makefile` - compilation
* `testing`
    * `FuzzTest.sh` - generates 'n' created puzzles
    * `UnitTester.sh` - implements unit testing 
* `puzzlefiles`: contains a variety of hard-coded puzzles, for testing purposes
* `ncurses` - extra credit interactive terminal functionality -- see README.md in ncurses directory for more information
    * `interface.h/interface.c` - header and driver file for terminal interaction
    * `Makefile` - compilation

### Compilation

To compile, simply `make`.

### Testing

For our testing our stragedy was centered around trying run as many cases as we possibly could and see how our code reacted. We made the test cases quite robust in order to accruately gauge our code's efficiency. There are three files to look at. 

1. FuzzTest.sh which is a shell script that takes one input from the user which is the number of tests to generate. This script will call the create function, save the output to a file that is then passed into the solve function, which will solve it and then return the solved sudoku to a different file called fuzz.out

2. Unit Testing- Our Unit Testing is all done in one shell script that calls the solve function and checks to see if it is properly working and generating valid sudokus. we check this by passing the sudokus to the solver and seeing if any errors arise. We also test solver directly by passing it invlaid sudokus of various types from incorrect formatting to incorrect numbers and even blank sudokus. Then we pass valid sudokus and compare the results to the right answer to make sure it is correct.

3. Testing.sh just runs make and make clean and then runs both of the tests previously mentioned. 

### Extra Credit

Our program showcases three additional features on top of the base guidelines for this assignment.

1. A mathematical proof for how, according to Group Theory, there is a possible way we could guarantee uniqueness for sudoku puzzles, although we did not implement this, due to time constraints. Please see the `Proof_Sudoku_Solutions.pdf` document for more details regarding this proof.

2. Options to choose difficulty level, 'easy', 'medium', or 'hard', as discussed above

3. A terminal interactive interface using the `ncurses` library. In particular, the program allows the user to manually insert numbers into the puzzle and use the WASD/arrow keys to navigate throughout the puzzle to see the different units' possibles list. This comes supported with color to distinguish between units that can be changed, and those part of the original puzzle that cannot be edited. 

Please find more details in the `ncurses README`. To keep our code organized, we have also decided to have a separate driver file for that program. To that end, you will need to separately navigate to the `ncurses` repository in order to make and test the program.
