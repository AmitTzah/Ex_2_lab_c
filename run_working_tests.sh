#! /usr/bin/env bash

gcc *.c -o my_grep
./working_tests/run1.sh
./working_tests/run2.sh
./working_tests/run3.sh
./working_tests/run4.sh
./working_tests/run5.sh