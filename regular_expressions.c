#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "regular_expression.h"
#include "identify_input_switches.h"

//private functions:

int check_for_dot(){

}

char *find_next_char(char *pattern, int index){
    E_structs_array e_array;
    if(pattern[index] == 0x5C)  // Ascii for '\' is 92
        return pattern[index+1];
    return pattern[index];
}