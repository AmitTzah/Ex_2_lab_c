//
// Created by Amit on 15/11/2021.
//


#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "identify_and_parse_input.h"
#include "match_pattern_to_line.h"



char * str_to_lowercase( char *str)
{

    int i = 0;
    while (str[i] != '\0'){

        str[i] = tolower(str[i]);
        i++;
    }
    str[i] = '\0';
    return str;
}

void flip_is_match(int * is_match,int is_v_on){

    if(is_v_on==1){

        if(*is_match==1){

            *is_match=0;
        }

        else{

            *is_match=1;
        }
    }
}


int is_word_ends(const char *word, int index){
    return ((word[index] == '\0') || (word[index] == '\r') || (word[index] == '\n'));
}
/*
char *find_current_pattern(char *str, char *pattern, int offset){
    char *temp_pattern = (char*) malloc(strlen(pattern));
    strcpy(temp_pattern, str);
    int i = strlen(temp_pattern);
    while (!is_word_ends(pattern, i) && pattern[i+offset] != 0x29) {
        temp_pattern[i] = pattern[i + offset];
        i++;
    }

        return temp_pattern;
}

int is_match_round_brackets(char *current_line, regular_exp_tav* regular_exp_tav_array, size_t size_of_array,
                            int* is_match, switches* swt,int* match_counter, char *pattern, size_t index){
    int option1 = 0, option2 = 0;
    char *temp_pattern = find_current_pattern(((regular_exp_tav_array[index]).regular_exp).round_brackets_tav.str1,
                                              pattern, strlen(((regular_exp_tav_array[index+1]).regular_exp).round_brackets_tav.str2)+3);

    regular_exp_tav_array[index].regular_exp.normal_tav = *temp_pattern;
    option1 = is_match_in_place(current_line,regular_exp_tav_array, index, size_of_array, is_match, swt, match_counter, temp_pattern);


    temp_pattern = find_current_pattern(((regular_exp_tav_array[index+1]).regular_exp).round_brackets_tav.str2,
                                        pattern, strlen(((regular_exp_tav_array[index]).regular_exp).round_brackets_tav.str1)+3);

    regular_exp_tav_array[index].regular_exp.normal_tav = *temp_pattern;
    option2 = is_match_in_place(current_line,regular_exp_tav_array, index+1, size_of_array, is_match, swt, match_counter, temp_pattern);

    regular_exp_tav_array[index].type_of_regular_exp.is_round_bracket = 1;

    free(temp_pattern);
    return option1||option2;

}
*/

int is_match_round_brackets(char *temp_line, regular_exp_tav* regular_exp_tav_array, size_t zero_index_of_pattern,
                            size_t size_of_array, char* temp_pattern, char *original_pattern){

    size_t size_of_current_pattern = size_of_array - zero_index_of_pattern;


    if((temp_pattern==NULL)&&(size_of_current_pattern == 0))
        return 1;
    if((*temp_pattern == *temp_line) && (is_word_ends(temp_line, 0)))
        return 1;
    if(*temp_pattern == 0)
        return is_match_in_place(temp_line, regular_exp_tav_array, zero_index_of_pattern+1, size_of_array,
                                 NULL, original_pattern);
    if(*temp_pattern == *temp_line) {

        return is_match_in_place(temp_line + 1, regular_exp_tav_array, zero_index_of_pattern, size_of_array,
                             temp_pattern + 1, original_pattern);
    }
    return is_match_in_place(temp_line + 1, regular_exp_tav_array, zero_index_of_pattern, size_of_array, original_pattern, original_pattern);
}


//checks if pattern matches to the first chars of current line.
int is_match_in_place(char *current_line, regular_exp_tav* regular_exp_tav_array, size_t zero_index_of_pattern,
                      size_t size_of_array, char* temp_pattern, char* original_pattern) {


    size_t size_of_current_pattern = size_of_array - zero_index_of_pattern;
    if((current_line==0 && size_of_current_pattern!=0) || (is_word_ends(current_line,0))){

        return 0;
    }
    if(size_of_current_pattern==0){
        return 1;
    }
    if((regular_exp_tav_array[zero_index_of_pattern]).regular_exp.point_tav.initialize_point == 1){
        return is_match_in_place(current_line+1, regular_exp_tav_array,zero_index_of_pattern+1
                                 , size_of_array, temp_pattern, original_pattern);
    }


    if((regular_exp_tav_array[zero_index_of_pattern]).type_of_regular_exp.is_square_brackets == 1){
        if((*current_line <= (regular_exp_tav_array[zero_index_of_pattern]).regular_exp.square_brackets_tav.max_val)
        && (*current_line >= (regular_exp_tav_array[zero_index_of_pattern]).regular_exp.square_brackets_tav.min_val))
            return 1;
        else
            return is_match_in_place(current_line+1, regular_exp_tav_array,
                                     zero_index_of_pattern, size_of_array, temp_pattern, original_pattern);
    }
    if((regular_exp_tav_array[zero_index_of_pattern]).type_of_regular_exp.is_round_bracket == 1) {
        char *temp_pattern_1, *temp_pattern_2 , *original_1, *original_2;

        if(temp_pattern == NULL) {
            temp_pattern_1 = ((regular_exp_tav_array)[zero_index_of_pattern].regular_exp.round_brackets_tav.str1);
            temp_pattern_2 = ((regular_exp_tav_array)[zero_index_of_pattern].regular_exp.round_brackets_tav.str2);
            original_1 = regular_exp_tav_array[zero_index_of_pattern].regular_exp.round_brackets_tav.str1;
            original_2 = regular_exp_tav_array[zero_index_of_pattern].regular_exp.round_brackets_tav.str2;

        }
        else {
            return is_match_round_brackets(current_line, regular_exp_tav_array, zero_index_of_pattern, size_of_array,
                                    temp_pattern,original_pattern);
        }

        return (is_match_round_brackets(current_line, regular_exp_tav_array, zero_index_of_pattern, size_of_array,
                                        temp_pattern_1, original_1)|| (is_match_round_brackets(current_line,regular_exp_tav_array,
                                                                                   zero_index_of_pattern,
                                                                                   size_of_array,temp_pattern_2, original_2)));
    }
    if((regular_exp_tav_array[zero_index_of_pattern]).regular_exp.normal_tav==*current_line){

        return is_match_in_place(current_line+1, regular_exp_tav_array,
                                 zero_index_of_pattern+1, size_of_array, temp_pattern, original_pattern);
    }
    return 0;

}




void match_in_case_e(char *current_line, regular_exp_tav* regular_exp_tav_array, size_t size_of_array, int* is_match,
                     switches* swt, int* match_counter, char *pattern){


    while((*current_line != '\n') && (*current_line != '\0') && *is_match==0) {
        *is_match = is_match_in_place(current_line,regular_exp_tav_array,0,size_of_array, NULL, pattern);
        current_line++;
    }

}
void match_in_case_x(char* current_line,char* pattern, int* is_match) {
    int i=0;
    while (pattern[i] != '\0'){
        if(pattern[i] != current_line[i]) {
            *is_match = 0;
            return;
        }
        i++;
    }
    if((current_line[i] == '\r') || (current_line[i] == '\n') || (current_line[i] == '\0'))
        *is_match =1;
    else
        *is_match=0;

}

void match_in_case_A(int* is_match,switches* switches_status, int* match_counter){
    if(*is_match==1) {
        (switches_status->a).line_remains_to_print = (switches_status->a).lines_to_print_case_A +1;
        if((switches_status->a).line_printed_since_match == (switches_status->a).lines_to_print_case_A)
            (switches_status->a).should_print_dash = 1;
    }

    else{
        (switches_status->a).line_remains_to_print--;
        if((switches_status->a).line_remains_to_print>0) {
            (switches_status->a).line_printed_since_match++;
            *is_match = 1;
            *match_counter-=1;
        }


    }

}

void match_in_case_i( char* current_line, char* pattern){
    str_to_lowercase(pattern);
    str_to_lowercase(current_line);
}

//public functions


int is_match_in_line(switches* switches_status, char* current_line, char* pattern, int* match_counter,
                     regular_exp_tav* array_of_reg_exp_tav,size_t size_of_array_of_reg_exp_tav){

    int is_match=0;

    if (strstr(current_line, pattern) != NULL && switches_status->no_switches==1) {
        is_match=1;

    }
    //this if statement should stay on top of all the rest of the cases.
    if(switches_status->i==1) {
        match_in_case_i( current_line, pattern);
    }


    if((switches_status->e).value == 1){

        match_in_case_e(current_line,array_of_reg_exp_tav,size_of_array_of_reg_exp_tav,&is_match, switches_status,
                        match_counter, pattern);

    }


    if(switches_status->x==1){
        match_in_case_x(current_line,pattern, &is_match);
    }

    if((strstr(current_line, pattern) != NULL) && (switches_status->x !=1))
        is_match=1;

    //Test for v case.
    flip_is_match(&is_match,switches_status->v);

    if((switches_status->a).value == 1){
        match_in_case_A(&is_match,switches_status,match_counter);
    }
    if(is_match){
        *match_counter+=1;
    }
    return is_match;
}
