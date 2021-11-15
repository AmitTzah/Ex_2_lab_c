#! /usr/bin/env tcsh

./my_grep change ./working_tests/in5 -i | diff ./working_tests/out5 -

valgrind --quiet --leak-check=yes ./my_grep change ./working_tests/in5 -i | diff ./working_tests/out5 -

