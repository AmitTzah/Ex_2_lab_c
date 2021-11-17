#ifndef CASES_H
#define CASES_H

#define NUMBER_OF_SWITCHES 8
#include <stdio.h>
#include "regular_expressions.h"

typedef struct case_A{
    int value;
    int lines_to_print_case_A;
    int line_remains_to_print;
}case_A;

typedef struct case_E{
    int value;
    char* pattern;
    E_structs_array E_array;
}case_E;

typedef struct switches_flags {
    int i;
    int v;
    int c;
    int n;
    int b;
    int x;
    case_A a;
    case_E e;
    int no_switches;
}switches;



switches check_switch_case(int argc, char **arguments_arr, int pattern_index);

int find_index_of_pattern_argument(int argc, char **arguments_arr);

ssize_t read_input_line(char ** current_line, size_t* n,FILE* fptr, int is_stdin_);

void open_file_or_stdin(FILE** fptr, char **arguments_arr,int is_stdin_, int pattern_index);

int is_stdin(int argc, char **arguments_arr, int pattern_index);

#endif