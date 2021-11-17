
#include "regular_expressions.h"


//private functions:

int check_for_dot(){
return 1;
}

char find_next_char(char *pattern, int index){
    //E_structs_array e_array;
    if(pattern[index] == 0x5C)  // Ascii for '\' is 5c
        return pattern[index+1];
    return pattern[index];
}


int check_if_dot(char* pattern){
    int i=1;
    while(pattern[i] != '\0') {
        if ((pattern[i] == 0x2e) && (pattern[i - 1] != 0x5c))
            return 1;
        i++;
    }
    return 0;
}

int check_if_circles(char* pattern){
    int i=1, left_side = 0, right_side = 0, separator = 0;
    while (pattern[i] != '\0'){
        if((pattern[i] == 0x28) && (pattern[i - 1] != 0x5c))
            left_side = 1;
        if((pattern[i] == 0x7c) && (left_side) && (pattern[i - 1] != 0x5c))
            separator = 1;
        if((pattern[i] == 0x29) && (left_side) && (separator) && (pattern[i - 1] != 0x5c))
            right_side = 1;
        i++;
    }
    return ((left_side) && (right_side) && (separator));
}