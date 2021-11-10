#! /usr/bin/env tcsh

./my_grep bla ./working_tests/bla | diff ./working_tests/bla -

valgrind --quiet --leak-check=yes ./my_grep bla ./working_tests/bla | diff ./working_tests/bla -
