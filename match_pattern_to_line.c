//
// Created by Amit on 15/11/2021.
//


#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "identify_input_switches.h"
#include "match_pattern_to_line.h"

//private functions
char * str_to_lowercase( char *str)
{

    int i = 0;
    while (str[i] != '\0'){

        str[i] = tolower(str[i]);
        i++;
    }
    str[i] = '\0';
    return str;
}

void ignore_letter_case(FILE *fptr, char *phrase){

    char *current_line = NULL, *lowerCase_line;
    size_t n;

    while(getline(&current_line, &n, fptr) != EOF){
        lowerCase_line = str_to_lowercase(current_line);
        if (strstr(lowerCase_line, phrase) != NULL)
            printf("%s", current_line);
    }
    free(current_line);
    fclose(fptr);


}


//public functions
int is_match_in_line(switches switches_status, int lines_counter ,char* current_line, char* pattern){

    if (strstr(current_line, pattern) != NULL && switches_status.no_switches==1) {
        return 1;

    }

    if(switches_status.i==1){
        str_to_lowercase(pattern);
        str_to_lowercase(current_line);

        if (strstr(current_line, pattern) != NULL){
            return 1;
        }

    }

    return 0;
}
