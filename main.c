#include <stdio.h>
#include <stdlib.h>

#include "identify_input_switches.h"
#include "print_outputs.h"
#include "match_pattern_to_line.h"

int main(int argc, char *argv[]) {

    char *current_line = NULL, *temp_line;
    size_t n;
    switches switches_status;
    int lines_counter = 0, is_match = 0;



    FILE *fptr= fopen(argv[2], "r");


    if (fptr ==NULL){
        printf("failed to open file!\n");
        exit(1);
    }

   switches_status = check_switch_case(argc, argv);

    while(getline(&current_line, &n, fptr) != EOF){
        lines_counter ++;
        temp_line = current_line;


        is_match = is_match_in_line(switches_status,lines_counter, temp_line,argv[1]);

        if(switches_status.i)
            temp_line = str_to_lowercase(temp_line);



        print_According_to_switches(switches_status,is_match,lines_counter,temp_line);

        is_match = 0;
    }
    free(current_line);
    fclose(fptr);

    return 0;
}
