#! /usr/bin/env tcsh

./my_grep change ./working_tests/in4 | diff ./working_tests/out4 -

valgrind --quiet --leak-check=yes ./my_grep bla ./working_tests/3lines | diff ./working_tests/out3 -

