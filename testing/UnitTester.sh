#!/bin/bash

#This is a shell script that will serve as a unit test for both create and solve

echo "Testing Sudoku Create"
echo "Generating 3 sudokus to the same file: create_test[1,2,3].txt"

../sudoku/sudoku create > create_test1.txt
../sudoku/sudoku create > create_test2.txt
../sudoku/sudoku create > create_test3.txt

echo "Making sure each sudoku generated is diffrent"


echo "Comparing 1 and 2"
if diff --brief create_test1.txt create_test2.txt; then
    echo "No Difference"
else
    echo "Both puzzles are different"
fi

echo "Comparing 2 and 3"
if diff --brief create_test2.txt create_test3.txt; then
    echo "No Difference"
else
    echo "Both puzzles are different"
fi

echo "Comparing 1 and 3"
if diff --brief create_test1.txt create_test3.txt; then
    echo "No Difference"
else
    echo "Both puzzles are different"
fi


echo "Testing Sudoku Solve with the created file if nothing went wrong check: create_test[1,2,3]_solution.out"
../sudoku/sudoku solve create_test1.txt >> create_test1_solution.out
../sudoku/sudoku solve create_test2.txt >> create_test2_solution.out
../sudoku/sudoku solve create_test3.txt >> create_test3_solution.out

echo "Now testing Sudoku Solver with edge cases"

echo "Passing invalid Puzzle"
../sudoku/sudoku solve ../puzzlefiles/badpuzzle.txt

#uncomment these two when we have a catcher for incorrect format errors and out of bound number entries

# echo "Passing invalid Puzzle Format"
# ../sudoku/sudoku solve ../puzzlefiles/invalid_format_puzzle.txt

# echo "Passing a sudoku with values outside of the bounds"
# ../sudoku/sudoku solve ../puzzlefiles/wrong_num.txt


echo "Passing 2 empty puzzles"
../sudoku/sudoku solve ../puzzlefiles/empty.txt >> nonunique.out 
../sudoku/sudoku solve ../puzzlefiles/empty.txt >> nonunique2.out 


if diff --brief nonunique.out nonunique2.out; then
    echo "No Difference between two different generations of the same empty puzzle"
else
    echo "empty_puzzle does not generate a unique solution"
fi

echo "Testing 2 valid puzzles"
../sudoku/sudoku solve ../puzzlefiles/easy.txt >> puzzle_test1_solution.out
../sudoku/sudoku solve ../puzzlefiles/test1.txt >> puzzle_test2_solution.out

echo "Comparing solver solution to actual solution"

if diff puzzle_test1_solution.out ../puzzlefiles/puzzle1_sol.txt; then
echo "No differences between puzzle1 solver generated solution and solution "
fi 

if diff --brief puzzle_test2_solution.out ../puzzlefiles/puzzle2_sol.txt; then 
echo "No differences between puzzle2 solver generated solution and solution "
fi 

#comment these removes out if you wanna see the solutions files generated
rm -rf create_*
rm -rf puzzle_test1_solution*
rm -rf puzzle_test2_solution*
rm -rf nonuni*



