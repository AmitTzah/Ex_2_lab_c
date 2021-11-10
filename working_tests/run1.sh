#! /usr/bin/env tcsh

./my_grep a ./working_tests/emptyfile | diff ./working_tests/emptyfile -

valgrind --quiet --leak-check=yes ./my_grep a ./working_tests/emptyfile | diff ./working_tests/emptyfile -

