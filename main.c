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

    switches switches_status;

    int lines_counter = 0, is_match = 0, bytes_counter = 0, match_counter = 0;
    int pattern_index=find_index_of_pattern_argument(argc, argv);

    char *temp_pattern= calloc((strlen(argv[pattern_index]))+1,sizeof(char));

    int is_stdin_=is_stdin(argc, argv, pattern_index);

    FILE *fptr=NULL;

    open_file_or_stdin(&fptr,argv,is_stdin_, pattern_index);

    strcpy(temp_pattern,argv[pattern_index]);
    switches_status = check_switch_case(argc, argv,pattern_index);

    while(read_input_line(&current_line, &n,fptr, is_stdin_) != EOF){
        lines_counter ++;
        temp_current_line= calloc((strlen(current_line))+1, sizeof(char));
        strcpy(temp_current_line,current_line);

        is_match = is_match_in_line(switches_status,lines_counter, temp_current_line,temp_pattern);
        match_counter += count_number_of_matches(switches_status, is_match);


        if((is_match)  && (switches_status.a.value == 1)){
            if (switches_status.a.line_remains_to_print > 0)
                is_match = 0;
            switches_status.a.line_remains_to_print = switches_status.a.lines_to_print_case_A +1;
        }

        print_According_to_switches(switches_status,is_match,lines_counter,match_counter, bytes_counter, current_line);


        is_match = 0;
        switches_status.a.line_remains_to_print --;
        bytes_counter += strlen(temp_current_line);
        free(temp_current_line);
    }

    c_case_print(switches_status, match_counter);

    free(current_line);
    free(temp_pattern);

    close_file_if_needed(fptr, is_stdin_);

    return 0;
}