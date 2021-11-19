#ifndef REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_H

typedef enum type_of_regular_exp{
    is_normal_tav = 0,
    is_point,
    is_round_brackets,
    is_square_brackets
} type_of_regular_exp;

typedef struct point{
int initialize_point;

}point;

typedef struct round_brackets{
    char* str1;
    char* str2;
}round_brackets;

typedef struct square_brackets{
    char min_val;
    char max_val;
}square_brackets;




typedef union regular_exp {
    char normal_tav;
    round_brackets* round_brackets_tav;
    square_brackets* square_brackets_tav;
    point * point_tav ;
}regular_exp;

typedef struct regular_exp_tav{
    type_of_regular_exp type_of_regular_exp;
    regular_exp    regular_exp;
}regular_exp_tav;

char find_next_char(char *pattern, int index);
int check_if_dot_reg_exp_in_given_pattern(char* pattern);
int check_if_circles_reg_exp_in_given_pattern(char* pattern);
int check_if_squares_reg_exp_in_given_pattern(char *pattern);
square_brackets find_squares_values(char *pattern);

#endif
