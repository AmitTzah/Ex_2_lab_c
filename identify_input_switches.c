
#include <string.h>


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
    }
    return switches_status;
}

int find_index_of_pattern_argument(int argc, char **arguments_arr){

    int i;
    for (i = 1; i < argc; i++) {
        if(arguments_arr[i][0]!='-'){
            return i;
        }
    }


}