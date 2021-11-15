#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "identify_input_switches.h"
#include "print_outputs.h"
#include "match_pattern_to_line.h"

int main(int argc, char *argv[]) {

    char *current_line = NULL;
    char* temp_current_line=NULL;

    char *temp_pattern= calloc((strlen(argv[1]))+2,sizeof(char));

    size_t n;
    switches switches_status;
    int lines_counter = 0, is_match = 0, bytes_counter = 0;

    int pattern_index=find_index_of_pattern_argument(argc, argv);


    FILE *fptr= fopen(argv[pattern_index+1], "r");


    if (fptr ==NULL){
        printf("failed to open file!\n");
        exit(1);
    }

    switches_status = check_switch_case(argc, argv);

    while(getline(&current_line, &n, fptr) != EOF){
        lines_counter ++;
        bytes_counter += strlen(current_line);
        temp_current_line= calloc((strlen(current_line))+2, sizeof(char));
        strcpy(temp_current_line,current_line);
        strcpy(temp_pattern,argv[pattern_index]);

        is_match = is_match_in_line(switches_status,lines_counter, temp_current_line,temp_pattern);

        print_According_to_switches(switches_status,is_match,lines_counter,bytes_counter, current_line);

        is_match = 0;
        free(temp_current_line);
    }
    free(current_line);
    free(temp_pattern);
    fclose(fptr);

    return 0;
}