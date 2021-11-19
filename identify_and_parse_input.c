
#include <string.h>
#include <stdlib.h>

#include "identify_and_parse_input.h"
#include "regular_expressions.h"

//private functions



//public functions.

switches check_switch_case(int argc, char **arguments_arr, size_t pattern_index) {
    int i;
    switches switches_status={0};

    switches_status.no_switches=1;


    for (i = 0; i < argc; i++) {
        if (!strcmp(arguments_arr[i], "-i")) {
            switches_status.i = 1;
            switches_status.no_switches=0;
        }
        if (!strcmp(arguments_arr[i], "-v")) {
            switches_status.v = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-c")) {
            switches_status.c = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-n")) {
            switches_status.n = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-b")) {
            switches_status.b = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-x")) {
            switches_status.x = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-A")) {
            switches_status.a.value = 1;
            switches_status.a.lines_to_print_case_A = atoi(arguments_arr[i+1]);
            switches_status.a.line_remains_to_print = 0;
            switches_status.a.line_printed_since_match = 0;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-E")) {
            switches_status.e.value = 1;
            switches_status.e.pattern = arguments_arr[pattern_index];

            switches_status.no_switches=0;

        }
    }
    return switches_status;
}


void open_file_or_stdin(FILE** fptr, char **arguments_arr,int is_stdin_, pattern_file_indexes pattern_file_indexes){

    if (is_stdin_)
    {

        if (!freopen(NULL, "r", stdin)) {
            printf("opening stdin for reading failed!");
            exit(1);
        }

    }
    else{

         *fptr= fopen(arguments_arr[pattern_file_indexes.file_index_if_given], "r");

        if (*fptr ==NULL){
            printf("failed to open file!\n");
            exit(1);
        }
    }

}
ssize_t read_input_line(char ** current_line, size_t* n,FILE* fptr, int is_stdin_)
{

    if (is_stdin_)
    {

        return getline(current_line, n, stdin);

    }
    else{

        return getline(current_line, n, fptr);
    }

}

int is_stdin(pattern_file_indexes pattern_file_indexes){

    if(pattern_file_indexes.file_index_if_given==0){

        return 1;
    }

    return 0;

}

void close_file_if_needed(FILE *fptr, int is_stdin_){

    if(is_stdin_==0){

        fclose(fptr);
    }

}

void find_index_of_pattern_and_file_arguments(int argc, char **arguments_arr,pattern_file_indexes* indexes){

    int i;
    for (i = 1; i < argc; i++) {
        if(arguments_arr[i][1] == 'A') {
            i += 1;
            continue;
        }
        if(arguments_arr[i][0]!='-'){
            indexes->pattern_index= i;
            break;
        }
    }
    i++;
    while(i<argc){

        if(arguments_arr[i][1] == 'A') {
            i += 1;
            continue;
        }
        if(arguments_arr[i][0]!='-'){
            indexes->file_index_if_given=i;
        }
        i++;
    }

}

void get_temp_pattern_parse_reg_exp(int argc, char **arguments_arr,pattern_file_indexes* indexes, switches switches_status,char **temp_pattern,regular_exp_tav* array_of_reg_exp_tav){

    if ((switches_status.e.value)==1){


    }

    else{

        *temp_pattern= calloc((strlen(arguments_arr[indexes->pattern_index]))+1,sizeof(char));
        strcpy(*temp_pattern,arguments_arr[indexes->pattern_index]);
    }

}