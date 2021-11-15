#ifndef CASES_H
#define CASES_H

#define NUMBER_OF_SWITCHES 7

typedef struct switches_flags {
    int i;
    int v;
    int c;
}switches;

switches check_switch_case(int argc, char **arguments_arr) ;
void print_According_to_v(switches swt, int is_match, char *line);
void print_According_to_c(switches swt, int is_match, int line_counter);
void  ignore_letter_case(FILE *fptr, char *phrase);
char *str_to_lowercase(const char *str);
void print_non_match_lines(FILE *fptr, char *phrase);

#endif