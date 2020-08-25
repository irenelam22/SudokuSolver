# CS50 Sudoku Final Project
### Team KIDD -- Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez

## Sudoku
Our project supports two features: generating a new 9x9 puzzle, or solving a given 9x9 puzzle. For the latter, the program takes in a puzzle-formatted file and prints to stdout the solution, if any.

Rules of sudoku: 
(1) each row will contain the values 1-9 (no duplicates), 
(2) each column will contain the values 1-9 (no duplicates), and  
(3) each box (3x3 grid) will contain the values 1-9 (no duplicates). 

### create

### solve

`solve` takes in a (presumably) unsolved puzzle and recursively populates each unit in the puzzle. In particular, each unit maintains a set of possible values (of which discludes values from the unit's row, column, and block). While this set is populated, the program attempts to insert one of these values into the puzzle, and backtraces to a previous unit if no such possible values exist. Solve continues this process until the entire puzzle is populated.

### Jargon used 

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
```

#### Solve module
```c
void solve(char* file_name);
bool solve_puzzle(puzzle_t* puzzle);
```

### Create module
```c
void create(char* file_name, int indicator);
static bool fill_puzzle(puzzle_t *puzzle); 
static bool hide_nums(puzzle_t *puzzle, puzzle_t *fullpuzz, int minshown); 
static bool has_one_solution(puzzle_t *puzzle, puzzle_t *fullpuzz); 
static void copy_puzzle(void *arg, unit_t* unit); 
```

Please run the following to execute `sudoku`:
`./sudoku create` to create a 9x9 puzzle

`./sudoku solve FILE_NAME` to solve a 9x9 puzzle
* where `FILE_NAME` is the pathname of a puzzle-formatted file, presumably 
  created by sudoku create

### Implementation

Please refer to `IMPLEMENTATION.md` for details regarding implementation.

### Assumptions

We made the same assumptions as those listed within the specs of this assignment, as well as those listed within this file. 

Additionally, we assumed that it is largely not possible to determine a unique solution given the requirements of this assignment (that at least 40 missing numbers are present in the generated puzzle). Please see our corresponding pseudo-proof for our reasoning behind this.

### Files

* `Makefile` - compilation procedure
* `solve/solve.c` - the implementation for solve
* `solve/solve.h` - the header file for solve 
* `create/create.c` - the implementation for create
* `create/create.h` - the header file for create 
* `IMPLEMENTATION.md` - implementation details 
* `DESIGN.md` - design specs 

### Compilation

To compile, simply `make`.

### Testing

The `testing.sh` script tests `querier` on numerous files for errors and edge cases. 

To test, simply `make` then `make test`.

Please find results in `testing.out`.
