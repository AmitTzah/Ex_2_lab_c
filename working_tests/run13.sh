#! /usr/bin/env tcsh

cat ./working_tests/in10 | ./my_grep -A 2 -c my_grep | diff ./working_tests/out13 -

cat ./working_tests/in10 | valgrind --quiet --leak-check=yes ./my_grep -A 2 -c my_grep | diff ./working_tests/out13 -
