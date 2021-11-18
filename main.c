#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "identify_input_switches.h"
#include "print_outputs.h"
#include "match_pattern_to_line.h"


int main(int argc, char *argv[]) {

    char *current_line = NULL;
    char* temp_current_line=NULL;


    size_t n;



    int lines_counter = 0, is_match=0, bytes_counter = 0, match_counter = 0;
    int pattern_index=find_index_of_pattern_argument(argc, argv);

    switches switches_status;

    switches_status = check_switch_case(argc, argv,pattern_index);
    switches* p_switches_status= &switches_status;


    char *temp_pattern= calloc((strlen(argv[pattern_index]))+1,sizeof(char));

    int is_stdin_=is_stdin(argc, argv, pattern_index);

    FILE *fptr=NULL;

    open_file_or_stdin(&fptr,argv,is_stdin_, pattern_index);

    strcpy(temp_pattern,argv[pattern_index]);


    while(read_input_line(&current_line, &n,fptr, is_stdin_) != EOF){
        lines_counter ++;
        temp_current_line= calloc((strlen(current_line))+1, sizeof(char));
        strcpy(temp_current_line,current_line);

        is_match = is_match_in_line(p_switches_status, temp_current_line,temp_pattern,&match_counter);


        print_According_to_switches(p_switches_status,is_match,lines_counter,&match_counter, bytes_counter, current_line);


        bytes_counter += strlen(temp_current_line);
        free(temp_current_line);
    }

    c_case_print(switches_status, match_counter);

    free(current_line);
    free(temp_pattern);

    close_file_if_needed(fptr, is_stdin_);

    return 0;
}