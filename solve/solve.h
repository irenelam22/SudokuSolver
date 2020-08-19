#include <stdio.h>
#include <stdlib.h>
#include "../common/unit.h"
#include "../common/puzzle.h"

#ifndef SOLVE_H
#define SOLVE_H

void solve_puzzle(puzzle_t* puzzle);
unit_t* next_unit(puzzle_t* puzzle);

#endif	# SOLVE_H
