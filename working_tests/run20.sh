#! /usr/bin/env tcsh

./my_grep -E -A 2 '\[(1|)(hey1|hey22)[0-9]\]' ./working_tests/in20 | diff ./working_tests/out20 -
valgrind --quiet --leak-check=yes ./my_grep -E -A 2 '\[(1|)(hey1|hey22)[0-9]\]' ./working_tests/in20 | diff ./working_tests/out20 -
