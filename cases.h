#ifndef CASES_H
#define CASES_H

typedef struct switches_flags {
    int i;
    int v;
    int c;
}switches;

switches check_switch_case(int argc, char **arguments_arr) ;
void print_According_to_v(switches swt, int ismatch, char *line);
void print_According_to_c(switches swt, int is_match, int line_counter);

void  ignore_letter_case(FILE *fptr, char *phrase);
#define NUMBER_OF_SWITCHES 7
char *str_to_lowercase(char *str);
void print_non_match_lines(FILE *fptr, char *phrase);

#endif