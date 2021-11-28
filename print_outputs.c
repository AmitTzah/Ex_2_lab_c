#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "identify_and_parse_input.h"
#include "print_outputs.h"

// private functions

// if the last line doesn't have a line break character, grep will add it.
void print_Line_break_after_the_last_line_if_needed(char *current_line)
{
  if (strchr(current_line, '\n') == NULL) {
    printf("\n");
  }
}

void print_According_to_n(switches *switches_status, int line_counter)
{

  if (switches_status->a.line_printed_since_match > 0) {
    printf("%d-", line_counter);
  } else {
    printf("%d:", line_counter);
  }
}
void print_According_to_b(size_t bytes_counter) { printf("%zu:", bytes_counter); }
void printer(char *line) { printf("%s", line); }

// public functions
void print_According_to_switches(switches *switches_status, int is_match, int lines_counter, int *match_counter,
                                 size_t bytes_counter, char *current_line)
{

  // check if we actually need to print something
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
    print_According_to_b(bytes_counter);
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
