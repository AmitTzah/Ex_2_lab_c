#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "identify_and_parse_input.h"

// Constants:
#define DOT_ASCII 0x2e
#define INCREMENT_INDEX_AFTER_ROUND_SETTING 2
#define INCREMENT_INDEX_AFTER_SQUARE_SETTING 4

// private functions
size_t increment_index_after_reg_set(round_brackets round_reg_exp)
{
  size_t i = 0;
  i += strlen((round_reg_exp.str1));
  i += strlen((round_reg_exp.str2));
  i += INCREMENT_INDEX_AFTER_ROUND_SETTING;
  return i;
}

size_t num_of_reg_exps_in_pattern(char *temp_pattern)
{
  size_t num_of_reg_exps_in_pattern = 0;
  int i;

  for (i = 0; i < strlen(temp_pattern); i++) {

    // check for (str|str)
    if ((temp_pattern[i] == LEFT_ROUND_BRACKET_ASCII) && (temp_pattern[i - 1] != BACKSLASH_ASCII)) {
      i++;
      while (temp_pattern[i] != RIGHT_ROUND_BRACKET_ASCII && (temp_pattern[i - 1] != BACKSLASH_ASCII)) {
        i++;
      }
      num_of_reg_exps_in_pattern++;
      continue;
    }
    // check for [x-y]
    if ((temp_pattern[i] == LEFT_SQUARE_BRACKET_ASCII) && (temp_pattern[i - 1] != BACKSLASH_ASCII)) {
      i++;
      while (temp_pattern[i] != RIGHT_SQUARE_BRACKET_ASCII && (temp_pattern[i - 1] != BACKSLASH_ASCII)) {
        i++;
      }
      num_of_reg_exps_in_pattern++;
      continue;
    }
    // check for  '\'
    if ((temp_pattern[i] == BACKSLASH_ASCII) &&
        ((temp_pattern[i - 1] != BACKSLASH_ASCII) ||
         ((temp_pattern[i - 1] == BACKSLASH_ASCII) && (temp_pattern[i - 2] == BACKSLASH_ASCII)))) {
      i++;
    }
    num_of_reg_exps_in_pattern++;
  }
  return num_of_reg_exps_in_pattern;
}

// public functions.
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

switches check_switch_case(int argc, char **arguments_arr)
{
  int i;
  switches switches_status = {0};

  switches_status.no_switches = 1;

  for (i = 0; i < argc; i++) {
    if (!strcmp(arguments_arr[i], "-i")) {
      switches_status.i = 1;
      switches_status.no_switches = 0;
    }
    if (!strcmp(arguments_arr[i], "-v")) {
      switches_status.v = 1;
      switches_status.no_switches = 0;
    }
    if (!strcmp(arguments_arr[i], "-c")) {
      switches_status.c = 1;
      switches_status.no_switches = 0;
    }
    if (!strcmp(arguments_arr[i], "-n")) {
      switches_status.n = 1;
      switches_status.no_switches = 0;
    }
    if (!strcmp(arguments_arr[i], "-b")) {
      switches_status.b = 1;
      switches_status.no_switches = 0;
    }
    if (!strcmp(arguments_arr[i], "-x")) {
      switches_status.x = 1;
      switches_status.no_switches = 0;
    }
    if (!strcmp(arguments_arr[i], "-A")) {
      switches_status.a.value = 1;
      switches_status.a.lines_to_print_case_A = atoi(arguments_arr[i + 1]);
      switches_status.a.line_remains_to_print = 0;
      switches_status.a.line_printed_since_match = 0;
      switches_status.a.was_there_a_non_matched_line_before_this_matched_line = 0;
      switches_status.no_switches = 0;
    }
    if (!strcmp(arguments_arr[i], "-E")) {
      switches_status.e.value = 1;

      switches_status.no_switches = 0;
    }
  }
  return switches_status;
}

void open_file_or_stdin(FILE **fptr, char **arguments_arr, int is_stdin_, pattern_file_indexes pattern_file_indexes)
{

  if (is_stdin_) {

    if (!freopen(NULL, "r", stdin)) {
      printf("opening stdin for reading failed!");
      exit(1);
    }

  } else {

    *fptr = fopen(arguments_arr[pattern_file_indexes.file_index_if_given], "r");

    if (*fptr == NULL) {
      printf("failed to open file!\n");
      exit(1);
    }
  }
}
ssize_t read_input_line(char **current_line, size_t *n, FILE *fptr, int is_stdin_)
{

  if (is_stdin_) {

    return getline(current_line, n, stdin);

  } else {

    return getline(current_line, n, fptr);
  }
}

int is_stdin(pattern_file_indexes pattern_file_indexes)
{

  if (pattern_file_indexes.file_index_if_given == 0) {

    return 1;
  }

  return 0;
}

void close_file_if_needed(FILE *fptr, int is_stdin_)
{

  if (is_stdin_ == 0) {

    fclose(fptr);
  }
}

void find_index_of_pattern_and_file_arguments(int argc, char **arguments_arr, pattern_file_indexes *indexes)
{

  int i;
  for (i = 1; i < argc; i++) {
    if ((arguments_arr[i][1] == 'A') && (arguments_arr[i][0] == '-')) {
      i += 1;
      continue;
    }
    if (arguments_arr[i][0] != '-') {
      indexes->pattern_index = i;
      break;
    }
  }
  i++;
  while (i < argc) {

    if (arguments_arr[i][1] == 'A') {
      i += 1;
      continue;
    }
    if (arguments_arr[i][0] != '-') {
      indexes->file_index_if_given = i;
    }
    i++;
  }
}

void get_temp_pattern(char **arguments_arr, pattern_file_indexes *indexes, char **temp_pattern)
{

  *temp_pattern = calloc((strlen(arguments_arr[indexes->pattern_index])) + 2, sizeof(char));
  strcpy((*temp_pattern) + 1, arguments_arr[indexes->pattern_index]);
}

void parse_reg_exp(switches switches_status, char *temp_pattern, regular_exp_tav **array_of_reg_exp_tav,
                   size_t *size_of_array_of_reg_exp_tav)
{
  size_t i = 0;
  int j = 0;
  *size_of_array_of_reg_exp_tav = num_of_reg_exps_in_pattern(temp_pattern);
  *array_of_reg_exp_tav = calloc((*size_of_array_of_reg_exp_tav), sizeof(struct regular_exp_tav));
  if (switches_status.i == 1) {
    str_to_lowercase(temp_pattern);
  }
  while ((i < strlen(temp_pattern)) && ((switches_status.e.value) == 1)) {

    if ((temp_pattern[i] == LEFT_ROUND_BRACKET_ASCII) && (temp_pattern[i - 1] != BACKSLASH_ASCII)) {
      set_arr_of_reg_exp_tav_round_bracket(array_of_reg_exp_tav, temp_pattern, j, i);
      i += increment_index_after_reg_set((((*array_of_reg_exp_tav)[j]).regular_exp.round_brackets_tav));
      j++;
      if (j == *size_of_array_of_reg_exp_tav) {
        break;
      }
    } else if ((temp_pattern[i] == LEFT_SQUARE_BRACKET_ASCII) && (temp_pattern[i - 1] != BACKSLASH_ASCII)) {
      set_arr_of_reg_exp_tav_square_bracket(array_of_reg_exp_tav, temp_pattern, j, i);
      i += INCREMENT_INDEX_AFTER_SQUARE_SETTING;
      j++;
      if (j == *size_of_array_of_reg_exp_tav) {
        break;
      }
    }

    else if ((temp_pattern[i] == DOT_ASCII) && (temp_pattern[i - 1] != BACKSLASH_ASCII)) {  // put point into array
      (((*array_of_reg_exp_tav)[j]).regular_exp).point_tav.initialize_point = 1;
      (((*array_of_reg_exp_tav)[j]).type_of_regular_exp).is_point = 1;
      j++;
      if (j == *size_of_array_of_reg_exp_tav) {
        break;
      }
    }

    else if ((temp_pattern[i] == BACKSLASH_ASCII) &&
             ((temp_pattern[i - 1] != BACKSLASH_ASCII) ||
              ((temp_pattern[i - 1] == BACKSLASH_ASCII) && (temp_pattern[i - 2] == BACKSLASH_ASCII)))) {
      i++;
      continue;
    } else {  // put normal_tav into array
      ((*array_of_reg_exp_tav)[j]).regular_exp.normal_tav = temp_pattern[i];
      ((*array_of_reg_exp_tav)[j]).type_of_regular_exp.is_normal_tav = 1;
      j++;
      if (j == *size_of_array_of_reg_exp_tav) {
        break;
      }
    }
    i++;
  }
}
