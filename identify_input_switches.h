#ifndef CASES_H
#define CASES_H

#define NUMBER_OF_SWITCHES 7
#include <stdio.h>

typedef struct switches_flags {
    int i;
    int v;
    int c;
    int no_switches;
}switches;


switches check_switch_case(int argc, char **arguments_arr) ;

int find_index_of_pattern_argument(int argc, char **arguments_arr);




#endif