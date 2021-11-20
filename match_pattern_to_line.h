//
// Created by Amit on 15/11/2021.
//

#ifndef EX_2_LAB_C_MATCH_PATTERN_TO_LINE_H
#define EX_2_LAB_C_MATCH_PATTERN_TO_LINE_H



int is_match_in_line(switches* switches_status, char* current_line, char* pattern, int* match_counter,
                     regular_exp_tav* array_of_reg_exp_tav,size_t size_of_array_of_reg_exp_tav);
int is_match_in_place(char *current_line, regular_exp_tav* regular_exp_tav_array,size_t zero_index_of_pattern,
                      size_t size_of_array, int* is_match,switches* swt, int* match_counter, char *pattern) ;



#endif //EX_2_LAB_C_MATCH_PATTERN_TO_LINE_H