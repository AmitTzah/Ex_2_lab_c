#! /usr/bin/env tcsh

./my_grep PattErn ./working_tests/in11 -i -n | diff ./working_tests/out11 -

valgrind --quiet --leak-check=yes ./my_grep PattErn ./working_tests/in11 -i -n | diff ./working_tests/out11 -