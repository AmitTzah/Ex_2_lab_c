//
// Created by Amit on 15/11/2021.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "identify_input_switches.h"
#include "print_outputs.h"


//private functions
void print_According_to_c(switches swt, int is_match, int line_counter){
    if(swt.v & (!is_match))
        printf("%d, ", line_counter);
    else if((!swt.v) & is_match)
        printf("%d, ", line_counter);
}
void print_According_to_v(switches swt, int is_match, char *line){

    if(swt.v & (!is_match))
        printf("%s", line);
    else if((!swt.v) & is_match)
        printf("%s", line);

}
void print_non_match_lines(FILE *fptr, char *phrase){

    char *current_line = NULL;
    size_t n;

    while(getline(&current_line, &n, fptr) != EOF){
        if (strstr(current_line, phrase) != NULL)
            continue;
        else
            printf("%s", current_line);
    }
    free(current_line);
    fclose(fptr);

}

//public functions
void print_According_to_switches(switches switches_status, int is_match, int lines_counter ,char* current_line ){

    if(switches_status.no_switches=1 && is_match==1){
        printf("%s", current_line);
    }
    if(switches_status.c) {
        print_According_to_c(switches_status, is_match, lines_counter);
    }
}

