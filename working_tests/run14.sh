#! /usr/bin/env tcsh

./my_grep PattErn ./working_tests/in11 -i -n -c | diff ./working_tests/out14 -

valgrind --quiet --leak-check=yes ./my_grep PattErn ./working_tests/in11 -i -n -c | diff ./working_tests/out14 -