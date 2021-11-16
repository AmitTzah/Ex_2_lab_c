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
int count_number_of_matches(switches swt, int is_match){
    if((swt.c == 1) && (is_match) && (!swt.v))
        return 1;
    else if((swt.c == 1) && (!is_match) && (swt.v))
        return 1;
}

int is_match_in_line(switches switches_status, int lines_counter , char* current_line, char* pattern){


    if((switches_status.a.value == 1) && (switches_status.a.line_remains_to_print > 0)){
        return 1;
    }

    if (strstr(current_line, pattern) != NULL && switches_status.no_switches==1) {
        return 1;

    }


    if(switches_status.i==1) {
        str_to_lowercase(pattern);
        str_to_lowercase(current_line);
    }

    if(switches_status.x==1){
        if(!strcmp(current_line,pattern))
            return 1;
        else
            return 0;
    }

    if(strstr(current_line, pattern) != NULL)
        return 1;


    return 0;
}