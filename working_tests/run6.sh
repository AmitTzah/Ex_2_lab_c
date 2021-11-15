#! /usr/bin/env tcsh

./my_grep -i bla ./working_tests/Capitals_bla | diff ./working_tests/Capitals_bla -

valgrind --quiet --leak-check=yes ./my_grep -i bla ./working_tests/Capitals_bla | diff ./working_tests/Capitals_bla -
