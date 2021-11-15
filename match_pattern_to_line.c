//
// Created by Amit on 15/11/2021.
//


#include <string.h>
#include <stdlib.h>

#include "identify_input_switches.h"
#include "match_pattern_to_line.h"

//public functions
int is_match_in_line(switches switches_status, int lines_counter ,char* current_line, char* pattern){

    if (strstr(current_line, pattern) != NULL)
        return  1;

}
