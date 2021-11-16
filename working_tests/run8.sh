#! /usr/bin/env tcsh

./my_grep line ./working_tests/case_n_input -b | diff ./working_tests/case_b_output -

valgrind --quiet --leak-check=yes ./my_grep line ./working_tests/case_n_input -b | diff ./working_tests/case_b_output -
