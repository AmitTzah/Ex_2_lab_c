#ifndef REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_H

#include <stdlib.h>

// Constants:

#define LEFT_ROUND_BRACKET_ASCII 0x28
#define RIGHT_ROUND_BRACKET_ASCII 0x29
#define LEFT_SQUARE_BRACKET_ASCII 0x5b
#define RIGHT_SQUARE_BRACKET_ASCII 0x5d
#define BACKSLASH_ASCII 0x5c

typedef struct type_of_regular_exp {
  int is_normal_tav;
  int is_point;
  char is_round_bracket;
  int is_square_brackets;
} type_of_regular_exp;

typedef struct point {
  int initialize_point;  // set point to 1 to indicate that it's a point

} point;

typedef struct round_brackets {
  char *str1;
  char *str2;
} round_brackets;

typedef struct square_brackets {
  char min_val;
  char max_val;
} square_brackets;

typedef union regular_exp {
  char normal_tav;
  round_brackets round_brackets_tav;
  square_brackets square_brackets_tav;
  point point_tav;
} regular_exp;

// a regular_exp_tav is (str1|str2) or 'char' or [x-y] or point.
// type_of_regular_exp is used to indicate which field inside the union is 'on'.
typedef struct regular_exp_tav {
  type_of_regular_exp type_of_regular_exp;
  regular_exp regular_exp;
} regular_exp_tav;

void set_arr_of_reg_exp_tav_round_bracket(regular_exp_tav **array_of_reg_exp_tav, char *pattern, int arr_index,
                                          size_t i);
void set_arr_of_reg_exp_tav_square_bracket(regular_exp_tav **array_of_reg_exp_tav, const char *pattern, int arr_index,
                                           size_t i);
void free_strings_inside_reg_array(regular_exp_tav *array_of_reg, size_t array_size);
#endif