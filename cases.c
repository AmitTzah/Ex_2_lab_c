#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cases.h"



char *str_to_lowercase(char *str)
{
    char *lower_str;
    int i = 0;
    while (str[i] != '\0'){

        lower_str[i] = tolower(str[i]);
        i++;
    }
    lower_str[i] = '\0';
    return lower_str;
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

void print_non_match_lines(FILE *fptr, char *phrase){

    char *current_line = NULL;
    size_t n;

    while(getline(&current_line, &n, fptr) != EOF){
        if (strstr(current_line, phrase) != NULL)
            continue;
        else
            printf("%s", current_line);
    }
    free(current_line);
    fclose(fptr);

}

switches check_switch_case(int argc, char **arguments_arr) {

    switches switches_status;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(arguments_arr[i], "-i")) {
            switches_status.i = 1;
        }
        if (!strcmp(arguments_arr[i], "-v")) {
            switches_status.v = 1;
        }
        if (!strcmp(arguments_arr[i], "-c")) {
            switches_status.c = 1;
        }
    }
    return switches_status;
}

void print_According_to_v(switches swt, int is_match, char *line){

    if(swt.v & (!is_match))
            printf("%s", line);
    else if((!swt.v) & is_match)
            printf("%s", line);

}
void print_According_to_c(switches swt, int is_match, int line_counter){
    if(swt.v & (!is_match))
        printf("%d, ", line_counter);
    else if((!swt.v) & is_match)
        printf("%d, ", line_counter);
}
