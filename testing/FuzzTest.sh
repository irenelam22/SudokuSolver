#!/bin/bash

# Fuzz Testing for Sudoku
# This bash file will take a commanline argument and generate an N test cases 
# then call solver and use it to test the generated grids to see which are valid

if [ $# -ne 1 ]; then 
    echo "Error invalid number of arguments "
    exit 1
fi 

echo "Generating $1 tests "
# echo "Look at the output file for the results" 

for (( i = 1; i <= $1; i++ )); 
do 
    echo "Sudoku Solution Number $i : " >> fuzz.out
    echo "Sudoku Number $i : " >> solve.out
    ../sudoku/sudoku create > testing.txt
    ../sudoku/sudoku solve testing.txt >> fuzz.out
    cat testing.txt >> solve.out
done

rm -rf testing.txt

echo "Fuzz Test Done: Please look at solve.out for sudoku generated"
echo "Fuzz Test Done: Please look at fuzz.out for solutions"
