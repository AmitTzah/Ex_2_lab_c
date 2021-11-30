#! /usr/bin/env tcsh

my_grep -E -x -i -A 0 '(AbJh|1232)(JmS|)1111.\.' ./working_tests/in21 | diff ./working_tests/out21 -
valgrind --quiet --leak-check=yes my_grep -E -x -i -A 0 '(AbJh|1232)(JmS|)1111.\.' ./working_tests/in21 | diff ./working_tests/out21 -
