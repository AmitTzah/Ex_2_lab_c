
#include <string.h>
#include <stdlib.h>

#include "identify_input_switches.h"


//public functions.

switches check_switch_case(int argc, char **arguments_arr) {
    int i;
    switches switches_status={0};
    switches_status.no_switches=1;


    for (i = 0; i < argc; i++) {
        if (!strcmp(arguments_arr[i], "-i")) {
            switches_status.i = 1;
            switches_status.no_switches=0;
        }
        if (!strcmp(arguments_arr[i], "-v")) {
            switches_status.v = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-c")) {
            switches_status.c = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-n")) {
            switches_status.n = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-b")) {
            switches_status.b = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-x")) {
            switches_status.x = 1;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-A")) {
            switches_status.a.value = 1;
            switches_status.a.lines_to_print_case_A = atoi(arguments_arr[i+1]);
            switches_status.a.line_remains_to_print = 0;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-E")) {
            switches_status.e.value = 1;
            switches_status.e.pattern = arguments_arr[i+1];

            switches_status.no_switches=0;

        }
    }
    return switches_status;
}
int find_index_of_pattern_argument(int argc, char **arguments_arr){

    int i;
    for (i = 1; i < argc; i++) {
        if(arguments_arr[i][1] == 'A') {
            i += 1;
            continue;
        }
        if(arguments_arr[i][0]!='-'){
            return i;
        }
    }


}