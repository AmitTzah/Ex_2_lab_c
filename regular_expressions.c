#include "regular_expressions.h"


//public functions:


char find_next_char(char *pattern, int index){
    if(pattern[index] == 0x5c) // Ascii for '\' is 5c
        return pattern[index +1];
    else
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
        if((pattern[i] == 0x29) &&  (separator) && (pattern[i - 1] != 0x5c))
            right_side = 1;
        i++;
    }
    return ((left_side) && (right_side) && (separator));
}

int check_if_squares(char *pattern){
    int i=1, left_side = 0, right_side = 0, middle = 0;
    while (pattern[i] != '\0'){
        if((pattern[i] == 0x5b) && (pattern[i - 1] != 0x5c))
            left_side = 1;
        if((pattern[i] ==0x2d) && left_side && (pattern[i - 1] != 0x5c))
            middle = 1;
        if((pattern[i] == 0x5d) && middle && (pattern[i - 1] != 0x5c))
            right_side = 1;
        i++;
    }
    return (left_side)  && (middle) && (right_side);
}

squares find_squares_values(char *pattern){
    int i=1;
    squares square_values;
    while (1){
        if(pattern[i] == 0x5b)
            square_values.min_val = pattern[i+1];
        if(pattern[i] == 0x2d){
            square_values.max_val = pattern[i+1];
            break;
        }
        i++;
    }
    return square_values;

}
