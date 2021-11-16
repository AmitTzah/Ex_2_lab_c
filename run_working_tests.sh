#! /usr/bin/env bash

gcc main.c identify_input_switches.c match_pattern_to_line.c print_outputs.c -o my_grep
./working_tests/run1.sh
./working_tests/run2.sh
./working_tests/run3.sh
./working_tests/run4.sh
./working_tests/run5.sh
./working_tests/run6.sh
./working_tests/run7.sh
./working_tests/run8.sh
