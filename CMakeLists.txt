cmake_minimum_required(VERSION 3.20)
project(Ex_2_lab_c C)

set(CMAKE_C_STANDARD 99)

add_executable(Ex_2_lab_c main.c identify_and_parse_input.c print_outputs.c print_outputs.h match_pattern_to_line.c match_pattern_to_line.h regular_expressions.c regular_expressions.h)
