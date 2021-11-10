#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cases.h"

int main(int argc, char *argv[]) {

    char *current_line = NULL, *temp_line;
    size_t n;
    switches switches_status;
    int c_counter = 0, is_match = 0;

    FILE *fptr= fopen(argv[argc -1], "r");

    if (fptr ==NULL)
        return 1;

    for(int i = 0; i < argc; i++){
        if(!strcmp(argv[i],"-i")){
            switches_status.i = 1;
        }
        if(!strcmp(argv[i],"-v")){
            switches_status.v = 1;
        }
        if(!strcmp(argv[i],"-c")){
            switches_status.c = 1;
        }

    }

    while(getline(&current_line, &n, fptr) != EOF){
        temp_line = current_line;

        if(switches_status.i)
            temp_line = str_to_lowercase(temp_line);

        if (strstr(temp_line, argv[argc - 2]) != NULL)
            is_match = 1;

        if(switches_status.v){
            if(is_match){
                is_match = 0;
                continue;
            }
            printf("%s", current_line);
        }
        else{
            if(is_match){
                is_match = 0;
                printf("%s", current_line);
        }
        }
    }
    free(current_line);
    fclose(fptr);

    return 0;
}
