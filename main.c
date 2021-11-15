#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cases.h"
#include "print_outputs.h"

int main(int argc, char *argv[]) {

    char *current_line = NULL, *temp_line;
    size_t n;
    switches switches_status;
    int lines_counter = 0, is_match = 0;

    FILE *fptr= fopen(argv[argc -1], "r");

    if (fptr ==NULL)
        return 1;

   switches_status = check_switch_case(argc, argv);



    while(getline(&current_line, &n, fptr) != EOF){
        lines_counter ++;
        temp_line = current_line;

        if(switches_status.i)
            temp_line = str_to_lowercase(temp_line);

        if (strstr(temp_line, argv[argc - 2]) != NULL)
            is_match = 1;

        print_According_to_switches(switches_status,is_match,lines_counter,current_line);

        is_match = 0;
    }
    free(current_line);
    fclose(fptr);

    return 0;
}
