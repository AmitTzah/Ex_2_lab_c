#include "regular_expressions.h"
#include <stdlib.h>
#include <string.h>

// Constants:
#define SEPERATOR_ASCII 0x7c
#define DASH_ASCII 0x2d

// public functions:

void set_arr_of_reg_exp_tav_round_bracket(regular_exp_tav **array_of_reg_exp_tav, char *pattern, int arr_index,
                                          size_t i)
{
  int k = 0;

  if ((pattern[i] == LEFT_ROUND_BRACKET_ASCII) && (pattern[i - 1] != BACKSLASH_ASCII)) {
    (((*array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str1 =
        (char *)calloc(strlen(pattern) + 1, sizeof(char));
    (((*array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str2 =
        (char *)calloc(strlen(pattern) + 1, sizeof(char));
    (((*array_of_reg_exp_tav)[arr_index]).type_of_regular_exp).is_round_bracket = 1;
    i++;
    while ((pattern[i] != SEPERATOR_ASCII) && (pattern[i - 1] != BACKSLASH_ASCII)) {
      (((*array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str1[k] = pattern[i];
      i++;
      k++;
    }
    (((*array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str1[k] = '\0';
    i++;
    k = 0;
    while ((pattern[i] != RIGHT_ROUND_BRACKET_ASCII) && (pattern[i - 1] != BACKSLASH_ASCII)) {
      (((*array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str2[k] = pattern[i];
      i++;
      k++;
    }
    (((*array_of_reg_exp_tav)[arr_index]).regular_exp).round_brackets_tav.str2[k] = '\0';
  }
}
void set_arr_of_reg_exp_tav_square_bracket(regular_exp_tav **array_of_reg_exp_tav, const char *pattern, int arr_index,
                                           size_t i)
{

  if (!((pattern[i] == LEFT_SQUARE_BRACKET_ASCII) && (pattern[i - 1] != BACKSLASH_ASCII))) {
    return;
  }

  (((*array_of_reg_exp_tav)[arr_index]).type_of_regular_exp).is_square_brackets = 1;
  while ((pattern[i] != RIGHT_SQUARE_BRACKET_ASCII) && (pattern[i - 1] != BACKSLASH_ASCII)) {
    if (pattern[i] == DASH_ASCII) {
      (((*array_of_reg_exp_tav)[arr_index]).regular_exp).square_brackets_tav.min_val = pattern[i - 1];
      (((*array_of_reg_exp_tav)[arr_index]).regular_exp).square_brackets_tav.max_val = pattern[i + 1];
    }
    i++;
  }
}

void free_strings_inside_reg_array(regular_exp_tav *array_of_reg, size_t array_size)
{
  int i;
  for (i = 0; i < array_size; i++) {
    if (array_of_reg[i].type_of_regular_exp.is_round_bracket) {
      free(array_of_reg[i].regular_exp.round_brackets_tav.str1);
      free(array_of_reg[i].regular_exp.round_brackets_tav.str2);
    }
  }
}