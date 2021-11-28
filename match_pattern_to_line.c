#include <ctype.h>
#include <string.h>

#include "identify_and_parse_input.h"
#include "match_pattern_to_line.h"

//Private functions:

char *str_to_lowercase(char *str)
{

  int i = 0;
  while (str[i] != '\0') {

    str[i] = tolower(str[i]);
    i++;
  }
  str[i] = '\0';
  return str;
}

void flip_is_match(int *is_match, int is_v_on)
{

  if (is_v_on == 1) {

    if (*is_match == 1) {

      *is_match = 0;
    }

    else {

      *is_match = 1;
    }
  }
}

int check_square_reg_logic(const char *current_line, regular_exp_tav *regular_exp_tav_array,
                           const size_t *zero_index_of_line, const size_t *zero_index_of_pattern)
{
  if ((current_line[*zero_index_of_line] <=
       (regular_exp_tav_array[*zero_index_of_pattern]).regular_exp.square_brackets_tav.max_val) &&
      (current_line[*zero_index_of_line] >=
       (regular_exp_tav_array[*zero_index_of_pattern]).regular_exp.square_brackets_tav.min_val)) {
    return 1;
  } else {
    return 0;
  }
}

int does_str_match_the_current_line_from_offset(char *temp_pattern, const size_t *zero_index_of_line,
                                                char *current_line)
{
  size_t i = (*zero_index_of_line);
  int j = 0;
  int is_match = 1;

  if (strlen(current_line + (*zero_index_of_line)) < strlen(temp_pattern)) {
    return 0;
  }
  while (current_line[i] != '\n' && current_line[i] != '\0' && temp_pattern[j] != '\0') {
    if (current_line[i] != temp_pattern[j]) {
      is_match = 0;
      break;
    }
    j++;
    i++;
  }
  return is_match;
}

int is_match_between_line_and_current_array_element(char *current_line, regular_exp_tav *regular_exp_tav_array,
                                                    size_t *zero_index_of_pattern, size_t *zero_index_of_line)
{
  int is_match, is_match_str_1, is_match_str_2;

  if ((regular_exp_tav_array[*zero_index_of_pattern]).type_of_regular_exp.is_normal_tav == 1) {
    if ((current_line[*zero_index_of_line]) == (regular_exp_tav_array[*zero_index_of_pattern]).regular_exp.normal_tav) {
      *zero_index_of_line = (*zero_index_of_line) + 1;
      is_match = 1;
    } else {
      *zero_index_of_line = (*zero_index_of_line) + 1;
      is_match = 0;
    }
  } else if ((regular_exp_tav_array[*zero_index_of_pattern]).regular_exp.point_tav.initialize_point == 1) {

    *zero_index_of_line = (*zero_index_of_line) + 1;
    is_match = 1;
  }

  else if ((regular_exp_tav_array[*zero_index_of_pattern]).type_of_regular_exp.is_round_bracket == 1) {

    char *temp_pattern_1 = ((regular_exp_tav_array)[*zero_index_of_pattern].regular_exp.round_brackets_tav.str1);
    char *temp_pattern_2 = ((regular_exp_tav_array)[*zero_index_of_pattern].regular_exp.round_brackets_tav.str2);

    is_match_str_1 = does_str_match_the_current_line_from_offset(temp_pattern_1, zero_index_of_line, current_line);
    is_match_str_2 = does_str_match_the_current_line_from_offset(temp_pattern_2, zero_index_of_line, current_line);

    if (is_match_str_1 == 1) {
      *zero_index_of_line = (*zero_index_of_line) + (strlen(temp_pattern_1));
    } else if (is_match_str_2 == 1) {
      *zero_index_of_line = (*zero_index_of_line) + (strlen(temp_pattern_2));
    }
    is_match = (is_match_str_2 | is_match_str_1);
  }
  // else- square brackets
  else {
    is_match = check_square_reg_logic(current_line, regular_exp_tav_array, zero_index_of_line, zero_index_of_pattern);
    *zero_index_of_line = (*zero_index_of_line) + 1;
  }

  *zero_index_of_pattern = (*zero_index_of_pattern) + 1;
  return is_match;
}

// checks if pattern matches to the first chars of current line.
int is_match_in_place(char *current_line, regular_exp_tav *regular_exp_tav_array, size_t *zero_index_of_pattern,
                      size_t zero_index_of_line, size_t size_of_array, switches *swt)
{
  int is_match = is_match_between_line_and_current_array_element(current_line, regular_exp_tav_array,
                                                                 zero_index_of_pattern, &zero_index_of_line);
  if (is_match == 1 && *zero_index_of_pattern == size_of_array) {
    return 1;
  } else if (is_match == 1 && *zero_index_of_pattern != size_of_array) {
    return is_match_in_place(current_line, regular_exp_tav_array, zero_index_of_pattern, zero_index_of_line,
                             size_of_array, swt);
  } else {
    return 0;
  }
}

void match_in_case_e(char *current_line, regular_exp_tav *regular_exp_tav_array, size_t size_of_array, int *is_match,
                     switches *swt, int* check_x_case_inside_e_case)
{
  size_t zero_index_of_pattern = 0;
  size_t zero_index_of_line = 0;
  int while_counter=0;

  while ((*current_line != '\n') && (*current_line != '\0') && *is_match == 0) {
    zero_index_of_pattern = 0;
    *is_match = is_match_in_place(current_line, regular_exp_tav_array, &zero_index_of_pattern, zero_index_of_line,
                                  size_of_array, swt);
    while_counter++;
    current_line++;
  }
  if(while_counter==1){
    *check_x_case_inside_e_case=1;
  }
}
void match_in_case_x(const char *current_line, const char *pattern, int *is_match)
{
  int i = 0;
  while (pattern[i] != '\0') {
    if (pattern[i] != current_line[i]) {
      *is_match = 0;
      return;
    }
    i++;
  }
  if ((current_line[i] == '\r') || (current_line[i] == '\n') || (current_line[i] == '\0')) {
    *is_match = 1;
  } else {
    *is_match = 0;
  }
}

void match_in_case_A(int *is_match, switches *switches_status, int *match_counter)
{
  if (*is_match == 1) {
    (switches_status->a).line_remains_to_print = (switches_status->a).lines_to_print_case_A + 1;
    if ((switches_status->a).line_printed_since_match == (switches_status->a).lines_to_print_case_A) {
      (switches_status->a).should_print_dash = 1;
    }
  }

  else {
    (switches_status->a).line_remains_to_print--;
    if ((switches_status->a).line_remains_to_print > 0) {
      (switches_status->a).line_printed_since_match++;
      *is_match = 1;
      *match_counter -= 1;
    }
  }
}

void match_in_case_i(char *current_line, char *pattern)
{
  str_to_lowercase(pattern);
  str_to_lowercase(current_line);
}

// public functions

int is_match_in_line(switches *switches_status, char *current_line, char *pattern, int *match_counter,
                     regular_exp_tav *array_of_reg_exp_tav, size_t size_of_array_of_reg_exp_tav)
{

  int is_match = 0;
  int check_x_case_inside_e_case=0;

  if (strstr(current_line, pattern) != NULL && switches_status->no_switches == 1) {
    is_match = 1;
  }
  // this if statement should stay on top of all the rest of the cases.
  if (switches_status->i == 1) {
    match_in_case_i(current_line, pattern);
  }
  if ((switches_status->e).value == 1) {
    match_in_case_e(current_line, array_of_reg_exp_tav, size_of_array_of_reg_exp_tav, &is_match,
                    switches_status,&check_x_case_inside_e_case);
  }

  if ((switches_status->e).value == 1 && switches_status->x == 1 ) {
    match_in_case_e(current_line, array_of_reg_exp_tav, size_of_array_of_reg_exp_tav, &is_match,
                    switches_status,&check_x_case_inside_e_case);
    is_match= is_match & check_x_case_inside_e_case;
  }

  if (switches_status->x == 1 && (switches_status->e).value != 1) {
    match_in_case_x(current_line, pattern, &is_match);
  }

  if ((strstr(current_line, pattern) != NULL) && (switches_status->x != 1)) {
    is_match = 1;
  }
  // Test for v case.
  flip_is_match(&is_match, switches_status->v);

  if ((switches_status->a).value == 1) {
    match_in_case_A(&is_match, switches_status, match_counter);
  }
  if (is_match) {
    *match_counter += 1;
  }
  return is_match;
}
