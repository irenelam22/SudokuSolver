#!/bin/bash

# This is a generalized testing script that will run both of the
# testing scripts in this directory as such the user will need to pass
# one argument which will represent the number of time FuzzTest will generate
# test cases. 


if [ $# -ne 1 ]; then 
    echo "Error invalid number of arguments "
    exit 1
fi 

set -e
make clean


/bin/bash ./FuzzTest.sh $1

/bin/bash ./UnitTester.sh
