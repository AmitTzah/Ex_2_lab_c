#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "identify_and_parse_input.h"
#include "print_outputs.h"
#include "match_pattern_to_line.h"


int main(int argc, char *argv[]) {

    pattern_file_indexes pattern_file_indexes={0};
    find_index_of_pattern_and_file_arguments(argc, argv,&pattern_file_indexes);

    size_t n;
    size_t bytes_counter=0;
    int lines_counter = 0, is_match, match_counter = 0;

    switches switches_status;
    switches_status = check_switch_case(argc, argv);
    switches* p_switches_status= &switches_status;

    int is_stdin_=is_stdin(pattern_file_indexes);
    FILE *fptr=NULL;
    open_file_or_stdin(&fptr,argv,is_stdin_, pattern_file_indexes);

    char *temp_pattern=NULL;
    regular_exp_tav* array_of_reg_exp_tav=NULL;
    size_t size_of_array_of_reg_exp_tav=0;
    get_temp_pattern(argv, &pattern_file_indexes, &temp_pattern);
    parse_reg_exp(switches_status,temp_pattern+1,&array_of_reg_exp_tav,&size_of_array_of_reg_exp_tav);

    char *current_line = NULL;
    char* temp_current_line=NULL;

    while(read_input_line(&current_line, &n,fptr, is_stdin_) != EOF){
        lines_counter ++;
        temp_current_line= calloc((strlen(current_line))+1, sizeof(char));
        strcpy(temp_current_line,current_line);

        is_match = is_match_in_line(p_switches_status, temp_current_line,temp_pattern+1,&match_counter,
                                    array_of_reg_exp_tav,size_of_array_of_reg_exp_tav);

        print_According_to_switches(p_switches_status,is_match,lines_counter,&match_counter, bytes_counter,
                                    current_line);

        bytes_counter += strlen(temp_current_line);

        free(temp_current_line);
    }

    c_case_print(switches_status, match_counter);

    free(current_line);
    free(temp_pattern);

    free_strings_inside_reg_array(array_of_reg_exp_tav,size_of_array_of_reg_exp_tav);
    free(array_of_reg_exp_tav);

    close_file_if_needed(fptr, is_stdin_);

    return 0;
}