#! /usr/bin/env tcsh

./my_grep -v change ./working_tests/in4 | diff ./working_tests/out4_v -

valgrind --quiet --leak-check=yes ./my_grep -v change ./working_tests/in4 | diff ./working_tests/oout4_v -
