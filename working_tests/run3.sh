#! /usr/bin/env tcsh

./my_grep bla ./working_tests/3lines | diff ./working_tests/out3 -

valgrind --quiet --leak-check=yes ./my_grep bla ./working_tests/3lines | diff ./working_tests/out3 -

