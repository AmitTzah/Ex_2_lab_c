#! /usr/bin/env tcsh

./my_grep -n -i -E 'o\.pdf' ~nimrodav/grep_tests/2013.html | diff ~nimrodav/grep_tests/out5 -

valgrind --quiet --leak-check=yes ./my_grep -n -i -E 'o\.pdf' ~nimrodav/grep_tests/2013.html | diff ~nimrodav/grep_tests/out5 -
