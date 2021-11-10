#ifndef CASES_H
#define CASES_H

typedef struct switches_flags {
    int i;
    int v;
    int c;
}switches;


void  ignore_letter_case(FILE *fptr, char *phrase);
#define NUMBER_OF_SWITCHES 7
char *str_to_lowercase(char *str);
void print_non_match_lines(FILE *fptr, char *phrase);

#endif