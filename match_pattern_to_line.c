//
// Created by Amit on 15/11/2021.
//


#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "identify_input_switches.h"
#include "match_pattern_to_line.h"


//private functions

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
int is_word_ends(const char *word, int index){
    return ((word[index] == '\0') || (word[index] == '\r') || (word[index] == '\n'));
}


int is_match_in_place(char *current_word, char* pattern, int index, int word_index){

    squares squares_values;
    if(check_if_circles(pattern))
        return is_match_reg_exp_circles(current_word, pattern);
    if(check_if_dot(pattern))
        return is_match_reg_exp_dot(current_word, pattern);
    if(check_if_squares(pattern)){
        squares_values = find_squares_values(pattern);
        if((pattern[index] == 0x5b) && (pattern[index-1] != 0x5c))
            if((current_word[word_index] >= squares_values.min_val) && (current_word[word_index] <= squares_values.max_val) && (is_word_ends(current_word, index)))
                return 1;
    }
    if(pattern[index] == 0x27)
        return 1;
    if(is_word_ends(current_word, word_index))
        return 0;
    if(find_next_char(pattern, index) != current_word[word_index]) {
        index = 1;
        return is_match_in_place(current_word, pattern, index, word_index+1);
    }

    if(pattern[index] == 0x5c)
        index++;
    return is_match_in_place(current_word, pattern, index + 1, word_index + 1);


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


//public functions


int is_match_in_line(switches* switches_status, char* current_line, char* pattern, int* match_counter){

    int is_match=0;

    if (strstr(current_line, pattern) != NULL && switches_status->no_switches==1) {
        is_match=1;

    }
    //this if statement should stay on top of all the rest of the cases.
    if(switches_status->i==1) {
        str_to_lowercase(pattern);
        str_to_lowercase(current_line);
    }


    if((switches_status->e).value == 1){
        int index_initiate = 1, match_found = 0, word_index =0;
        char *blank = " ", *current_word;
        current_word= calloc((strlen(current_line))+1, sizeof(char));
        current_word = strtok(current_line, blank);
        while(current_word != NULL) {
            if(is_match_in_place(current_word, pattern, index_initiate, word_index)) {
                is_match=1;
            }
            current_word = strtok(NULL, blank);

        }
    }



    if(switches_status->x==1){
        if(!strcmp(current_line,pattern))
            is_match=1;
        else
            is_match=0;
    }

    if(strstr(current_line, pattern) != NULL)
        is_match=1;

    //Test for v case.
    flip_is_match(&is_match,switches_status->v);

    if((switches_status->a).value == 1){

        if(is_match==1) {
            (switches_status->a).line_remains_to_print = (switches_status->a).lines_to_print_case_A +1;
            if((switches_status->a).line_printed_since_match == (switches_status->a).lines_to_print_case_A)
                (switches_status->a).should_print_dash = 1;
        }

        else{
            (switches_status->a).line_remains_to_print--;
            if((switches_status->a).line_remains_to_print>0) {
                (switches_status->a).line_printed_since_match++;
                is_match = 1;
                *match_counter-=1;
            }


        }
    }
    if(is_match){
        *match_counter+=1;
    }
    return is_match;
}

