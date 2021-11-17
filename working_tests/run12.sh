#! /usr/bin/env tcsh

./my_grep PattErn ./working_tests/in12 -i -n -v | diff ./working_tests/out12 -

valgrind --quiet --leak-check=yes ./my_grep PattErn ./working_tests/in12 -i -n -v | diff ./working_tests/out12 -