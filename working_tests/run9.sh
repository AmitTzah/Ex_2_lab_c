#! /usr/bin/env tcsh

cat ~nimrodav/grep_tests/3lines | ./my_grep bla | diff ~nimrodav/grep_tests/out3 -

cat ~nimrodav/grep_tests/3lines | valgrind --quiet --leak-check=yes ./my_grep bla | diff ~nimrodav/grep_tests/out3 -
