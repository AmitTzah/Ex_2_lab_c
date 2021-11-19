//
// Created by Amit on 15/11/2021.
//


#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "identify_and_parse_input.h"
#include "match_pattern_to_line.h"


//private functions

/*
int is_match_reg_exp_circles(char *current_word, char *pattern){
    char *temp1 = calloc(strlen(pattern), sizeof(char));
    char *temp2 = calloc(strlen(pattern), sizeof(char));
    int i=2, j=0, k=1;
    temp1[j]= 0x27;
    temp2[j]= 0x27;
    j++;
    while (pattern[i] != 0x7c){
        temp1[j] = pattern[i];
        i++;
        j++;
    }
    i++;
    while (pattern[i] != 0x29){
        temp2[k] = pattern[i];
        i++;
        k++;
    }
    i++;
    while(pattern[i] != '\0'){
        temp1[j] = pattern[i];
        temp2[k] = pattern[i];
        i++;
        j++;
        k++;
    }
    j=1;
    k=1;
    i=0;
    return (is_match_in_place(current_word, temp1, j, i) || is_match_in_place(current_word, temp2, k, i));

}
*/

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

int is_match_reg_exp_dot(char *current_word, char* pattern){

    char *temp_pattern = calloc(strlen(pattern), sizeof(char));
    int i=1;
    while (pattern[i] != 0x2e){
        temp_pattern[i-1] = pattern[i];
        i++;
    }

    if (strstr(current_word, temp_pattern) != NULL)
        return 1;
    else
        return 0;
}


int is_word_ends(const char *word, int index){
    return ((word[index] == '\0') || (word[index] == '\r') || (word[index] == '\n'));
}


//checks if pattern matches to the first chars of current line.
int is_match_in_place(char *current_line, regular_exp_tav* regular_exp_tav_array, size_t zero_index_of_pattern,size_t size_of_array) {

    size_t size_of_current_pattern = size_of_array - zero_index_of_pattern;
    if(current_line==0 && size_of_current_pattern!=0){

        return 0;
    }
    if(size_of_current_pattern==0){

        return 1;
    }
    if((regular_exp_tav_array[zero_index_of_pattern]).regular_exp.normal_tav==*current_line){

        return is_match_in_place(current_line+1,regular_exp_tav_array,zero_index_of_pattern+1,size_of_array);
    }
    return 0;

}
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




void match_in_case_e(char *current_line, regular_exp_tav* regular_exp_tav_array, size_t size_of_array, int* is_match){


    while(*current_line != '\n' && *is_match==0) {
       *is_match=is_match_in_place(current_line,regular_exp_tav_array,0,size_of_array);
        current_line++;
    }

}
void match_in_case_x(char* current_line,char* pattern, int* is_match) {
    if (!strcmp(current_line, pattern))
        *is_match = 1;
    else
        *is_match = 0;


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


int is_match_in_line(switches* switches_status, char* current_line, char* pattern, int* match_counter,regular_exp_tav* array_of_reg_exp_tav,size_t size_of_array_of_reg_exp_tav){

    int is_match=0;

    if (strstr(current_line, pattern) != NULL && switches_status->no_switches==1) {
        is_match=1;

    }
    //this if statement should stay on top of all the rest of the cases.
    if(switches_status->i==1) {
        match_in_case_i( current_line, pattern);
    }


    if((switches_status->e).value == 1){
         match_in_case_e(current_line,array_of_reg_exp_tav,size_of_array_of_reg_exp_tav,&is_match);

    }


    if(switches_status->x==1){
        match_in_case_x(current_line,pattern, &is_match);
    }

    if(strstr(current_line, pattern) != NULL)
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

