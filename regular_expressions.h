#ifndef REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_H



typedef struct point{


}point;

typedef struct round_brackets{
    char* str1;
    char* str2;
}round_brackets;

typedef struct square_brackets{
    char min_val;
    char max_val;
}square_brackets;

char find_next_char(char *pattern, int index);
int check_if_dot(char* pattern);
int check_if_circles(char* pattern);
int check_if_squares(char *pattern);
square_brackets find_squares_values(char *pattern);

#endif