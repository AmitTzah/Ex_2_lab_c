#ifndef CASES_H
#define CASES_H

#define NUMBER_OF_SWITCHES 8
#include <stdio.h>
#include "regular_expressions.h"

typedef struct pattern_file_indexes{
   size_t pattern_index;
   size_t file_index_if_given;

}pattern_file_indexes;

typedef struct case_A{
    int value;
    int lines_to_print_case_A;
    int line_remains_to_print;
    int line_printed_since_match;
    int should_print_dash;
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



switches check_switch_case(int argc, char **arguments_arr, size_t pattern_index);

void find_index_of_pattern_and_file_arguments(int argc, char **arguments_arr,pattern_file_indexes* indexes);

ssize_t read_input_line(char ** current_line, size_t* n,FILE* fptr, int is_stdin_);

void open_file_or_stdin(FILE** fptr, char **arguments_arr,int is_stdin_, pattern_file_indexes pattern_file_indexes);

int is_stdin(pattern_file_indexes pattern_file_indexes);

void close_file_if_needed(FILE *fptr, int is_stdin_);
#endif