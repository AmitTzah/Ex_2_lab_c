//
// Created by Amit on 15/11/2021.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "identify_and_parse_input.h"
#include "print_outputs.h"


//private functions

//if the last line doesn't have a line break character, grep will add it.
void print_Line_break_after_the_last_line_if_needed( char* current_line){
    if(strchr(current_line,'\n')==NULL ){
        printf("\n");

    }

}

void print_According_to_n( int line_counter){

        printf("%d:", line_counter);
}
void print_According_to_b( int bytes_counter){

        printf("%d:", bytes_counter);
}
void printer( char *line){

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
void print_According_to_switches(switches* switches_status, int is_match, int lines_counter , int* match_counter, int bytes_counter, char* current_line ){

    //check if we actually need to print something
    if(is_match==0){

        return;
    }

    if(switches_status->c) {
        return;
    }
    if(switches_status->no_switches==1){
        printf("%s", current_line);
        print_Line_break_after_the_last_line_if_needed(current_line);
        return;
    }

    if((switches_status->a).should_print_dash) {
        printf("--\n");
        (switches_status->a).should_print_dash = 0;

    }

    if(switches_status->n) {
        print_According_to_n( lines_counter);
    }

    if(switches_status->b) {
        print_According_to_b( bytes_counter);
    }

    printer( current_line);
    print_Line_break_after_the_last_line_if_needed(current_line);

}

void c_case_print(switches switches_status, int match_counter){
    if(switches_status.c) {
        printf("%d\n", match_counter);

    }
}



