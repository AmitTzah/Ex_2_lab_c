#! /usr/bin/env tcsh

./my_grep -E -i -n -x '\[(5|)[0-9](ororor|111)....(hellohellohello|fuckthisexcersize)\\\]' ./working_tests/in17 | diff ./working_tests/out17 -
valgrind --quiet --leak-check=yes ./my_grep -E -i -n -x '\[(5|)[0-9](ororor|111)....(hellohellohello|fuckthisexcersize)\\\]' ./working_tests/in17 | diff ./working_tests/out17 -
