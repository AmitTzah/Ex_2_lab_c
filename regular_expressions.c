#include "regular_expressions.h"
#include <string.h>
#include <stdlib.h>


//public functions:


char find_next_char(char *pattern, int index){
    if(pattern[index] == 0x5c) // Ascii for '\' is 5c
        return pattern[index +1];
    else
        return pattern[index];
}

void set_arr_of_reg_exp_tav_round_bracket(regular_exp_tav** array_of_reg_exp_tav, char *pattern,int arr_index,
                                          size_t i){
    int k=0;

    if((pattern[i] == 0x28) && (pattern[i-1] != 0x5c)){
        ((*(array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str1 = (char *)malloc(strlen(pattern));
        ((*(array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str2 = (char *)malloc(strlen(pattern));
        ((*(array_of_reg_exp_tav)[arr_index]).type_of_regular_exp).is_round_bracket = 1;
        i++;
        while ((pattern[i] != 0x7c) && (pattern[i-1] != 0x5c)){
            (((array_of_reg_exp_tav)[arr_index])->regular_exp).round_brackets_tav.str1[k] = pattern[i];
            i++;
            k++;
        }
        ((*(array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str1[k] = '\0';
        i++;
        k=0;
        while ((pattern[i] != 0x29) && (pattern[i-1] != 0x5c)) {
            (((array_of_reg_exp_tav)[arr_index])->regular_exp).round_brackets_tav.str2[k] = pattern[i];
            i++;
            k++;
        }
        ((*(array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str2[k] = '\0';
    }
}
void set_arr_of_reg_exp_tav_square_bracket(regular_exp_tav** array_of_reg_exp_tav, char *pattern,
                                           int arr_index,size_t  i){


    if(!((pattern[i] == 0x5b) && (pattern[i-1] != 0x5c)))
        return;

    (((*array_of_reg_exp_tav)[arr_index]).type_of_regular_exp).is_square_brackets = 1;
    while ((pattern[i] != 0x5d) && (pattern[i-1] != 0x5c)) {
        if(pattern[i] == 0x2d){
            (((*array_of_reg_exp_tav)[arr_index]).regular_exp).square_brackets_tav.min_val = pattern[i-1];
            (((*array_of_reg_exp_tav)[arr_index]).regular_exp).square_brackets_tav.max_val = pattern[i+1];
        }
        i++;
    }
}





int check_if_dot_reg_exp_in_given_pattern(char* pattern){
    int i=1;
    while(pattern[i] != '\0') {
        if ((pattern[i] == 0x2e) && (pattern[i - 1] != 0x5c))// Ascii for '.' is 2e
            return 1;
        i++;
    }
    return 0;
}


int check_if_squares_reg_exp_in_given_pattern(char *pattern){
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

square_brackets find_squares_values(char *pattern){
    int i=1;
    square_brackets square_values;
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

void free_strings_inside_reg_array(regular_exp_tav * array_of_reg, size_t array_size){
    int i;
    for(i=0; i<array_size; i++){
        if(array_of_reg[i].type_of_regular_exp.is_round_bracket){
            free(array_of_reg[i].regular_exp.round_brackets_tav.str1);
            free(array_of_reg[i].regular_exp.round_brackets_tav.str2);
        }

    }


}