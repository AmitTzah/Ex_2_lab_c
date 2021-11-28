#! /usr/bin/env tcsh

./my_grep -E '\[(1|)(hey1|hey22)[0-9]\]' ./working_tests/in16 | diff ./working_tests/out16 -
valgrind --quiet --leak-check=yes ./my_grep -E '\[(1|)(hey1|hey22)[0-9]\]' ./working_tests/in16 | diff ./working_tests/out16 -
