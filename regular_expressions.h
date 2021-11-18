#ifndef REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_H



typedef struct E_structs_array{
    char tav;

}E_structs_array;

typedef struct squares_regular_expression{
    char *min_val;
    char *max_val;
}squares;

char find_next_char(char *pattern, int index);
int check_if_dot(char* pattern);
int check_if_circles(char* pattern);
int check_if_squares(char *pattern);
squares find_squares_values(char *pattern);

#endif