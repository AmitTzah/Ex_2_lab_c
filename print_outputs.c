#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "identify_and_parse_input.h"
#include "print_outputs.h"

// private functions

void print_Line_break_after_the_last_line_if_needed(char *current_line)
{
  if (strchr(current_line, '\n') == NULL) {
    printf("\n");
  }
}

void print_According_to_n(switches *switches_status, int line_counter)
{
  int is_it_a_pattern_match = 0;
  if ((switches_status->a).line_remains_to_print == (switches_status->a).lines_to_print_case_A + 1) {

    is_it_a_pattern_match = 1;
  }

  if (switches_status->a.line_printed_since_match > 0 && !is_it_a_pattern_match) {
    printf("%d-", line_counter);
  } else {
    printf("%d:", line_counter);
  }
}
void print_According_to_b(size_t bytes_counter, switches *switches_status)
{

  int is_it_a_pattern_match = 0;
  if ((switches_status->a).line_remains_to_print == (switches_status->a).lines_to_print_case_A + 1) {

    is_it_a_pattern_match = 1;
  }

  if (switches_status->a.line_printed_since_match > 0 && !is_it_a_pattern_match) {
    printf("%zu-", bytes_counter);
  } else {
    printf("%zu:", bytes_counter);
  }
}
void printer(char *line) { printf("%s", line); }

// public functions
void print_According_to_switches(switches *switches_status, int is_match, int lines_counter, int *match_counter,
                                 size_t bytes_counter, char *current_line)
{

  if (is_match == 0) {
    return;
  }

  if (switches_status->c) {
    return;
  }
  if (switches_status->no_switches == 1) {
    printf("%s", current_line);
    print_Line_break_after_the_last_line_if_needed(current_line);
    return;
  }

  if ((switches_status->a).should_print_dash) {
    printf("--\n");
    (switches_status->a).should_print_dash = 0;
  }

  if (switches_status->n) {
    print_According_to_n(switches_status, lines_counter);
  }

  if (switches_status->b) {
    print_According_to_b(bytes_counter, switches_status);
  }

  printer(current_line);
  print_Line_break_after_the_last_line_if_needed(current_line);
}

void c_case_print(switches switches_status, int match_counter)
{
  if (switches_status.c) {
    printf("%d\n", match_counter);
  }
}
