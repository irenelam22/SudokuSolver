#include "../common/puzzle.h"
#include "../common/unit.h"
#include "solve.h"

int main(const int argc, const char *argv[])
{
    puzzle_t *puzzle = puzzle_new(); 
    unit_t* cell = choose_unit(puzzle);
    return 0;
}

