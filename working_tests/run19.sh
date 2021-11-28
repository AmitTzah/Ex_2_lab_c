#! /usr/bin/env tcsh

./my_grep -n -A 5 -b -i -E 'o\.pdf' ~nimrodav/grep_tests/2013.html | diff ./working_tests/out19 -

valgrind --quiet --leak-check=yes ./my_grep -n -A 5 -b -i -E 'o\.pdf' ~nimrodav/grep_tests/2013.html | diff ./working_tests/out19 -
