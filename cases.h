#ifndef CASES_H
#define CASES_H

#define NUMBER_OF_SWITCHES 7

typedef struct switches_flags {
    int i;
    int v;
    int c;
    int no_switches;
}switches;


switches check_switch_case(int argc, char **arguments_arr) ;
void  ignore_letter_case(FILE *fptr, char *phrase);


char *str_to_lowercase(const char *str);


#endif