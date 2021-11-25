#include <string.h>
#include <stdlib.h>

#include "identify_and_parse_input.h"




//private functions


//public functions.

size_t num_of_reg_exps_in_pattern(char* temp_pattern){
    size_t num_of_reg_exps_in_pattern=0;
    int i;

    //TODO break this code in functions to avoid code duplication



    for (i = 0; i < strlen(temp_pattern); i++) {

        // check for (str|str)
        if ((temp_pattern[i] == 0x28) && (temp_pattern[i - 1] != 0x5c)){ //0x28= '(' ,Ascii for '\' is 5c
            i++;
            while(temp_pattern[i] != 0x29 && (temp_pattern[i - 1] != 0x5c))
            {
                i++;
            }

            num_of_reg_exps_in_pattern ++;
            continue;
        }
        // check for [x-y]
        if ((temp_pattern[i] == 0x5b) && (temp_pattern[i - 1] != 0x5c)){ //0x28= '(' ,Ascii for '\' is 5c
            i++;
            while(temp_pattern[i] != 0x5d && (temp_pattern[i - 1] != 0x5c))
            {
                i++;
            }
            num_of_reg_exps_in_pattern++;
            continue;
        }
        //check for  '\'
        if(temp_pattern[i] == 0x5c){
            i++;
        }


    }

    return num_of_reg_exps_in_pattern;

}




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
            switches_status.a.line_printed_since_match = 0;
            switches_status.no_switches=0;

        }
        if (!strcmp(arguments_arr[i], "-E")) {
            switches_status.e.value = 1;

            switches_status.no_switches=0;

        }
    }
    return switches_status;
}


void open_file_or_stdin(FILE** fptr, char **arguments_arr,int is_stdin_, pattern_file_indexes pattern_file_indexes){

    if (is_stdin_)
    {

        if (!freopen(NULL, "r", stdin)) {
            printf("opening stdin for reading failed!");
            exit(1);
        }

    }
    else{

        *fptr= fopen(arguments_arr[pattern_file_indexes.file_index_if_given], "r");

        if (*fptr ==NULL){
            printf("failed to open file!\n");
            exit(1);
        }
    }

}
ssize_t read_input_line(char ** current_line, size_t* n,FILE* fptr, int is_stdin_)
{

    if (is_stdin_)
    {

        return getline(current_line, n, stdin);

    }
    else{

        return getline(current_line, n, fptr);
    }

}

int is_stdin(pattern_file_indexes pattern_file_indexes){

    if(pattern_file_indexes.file_index_if_given==0){

        return 1;
    }

    return 0;

}

void close_file_if_needed(FILE *fptr, int is_stdin_){

    if(is_stdin_==0){

        fclose(fptr);
    }

}

void find_index_of_pattern_and_file_arguments(int argc, char **arguments_arr,pattern_file_indexes* indexes){

    int i;
    for (i = 1; i < argc; i++) {
        if(arguments_arr[i][1] == 'A') {
            i += 1;
            continue;
        }
        if(arguments_arr[i][0]!='-'){
            indexes->pattern_index= i;
            break;
        }
    }
    i++;
    while(i<argc){

        if(arguments_arr[i][1] == 'A') {
            i += 1;
            continue;
        }
        if(arguments_arr[i][0]!='-'){
            indexes->file_index_if_given=i;
        }
        i++;
    }

}

void get_temp_pattern( char **arguments_arr,pattern_file_indexes* indexes,char **temp_pattern){

    *temp_pattern= calloc((strlen(arguments_arr[indexes->pattern_index]))+2,sizeof(char));
    strcpy((*temp_pattern)+1,arguments_arr[indexes->pattern_index]);


}

void parse_reg_exp(switches switches_status,char* temp_pattern,regular_exp_tav** array_of_reg_exp_tav,
                   size_t* size_of_array_of_reg_exp_tav){
    size_t i;
    int j=0;

    *size_of_array_of_reg_exp_tav =num_of_reg_exps_in_pattern(temp_pattern);
    *array_of_reg_exp_tav=calloc((*size_of_array_of_reg_exp_tav),sizeof(struct regular_exp_tav));

    if ((switches_status.e.value)==1){


        //TODO break this code into functions to avoid code duplication
        // Write (str|str) and [x-y] cases.

        for (i=0; i < strlen(temp_pattern); i++) {

            // put (str|str) into array
            set_arr_of_reg_exp_tav_round_bracket(array_of_reg_exp_tav, temp_pattern, j,i);
            if((((*array_of_reg_exp_tav)[j]).type_of_regular_exp).is_round_bracket == 1) {
                i += strlen((((*array_of_reg_exp_tav)[j]).regular_exp).round_brackets_tav.str1);
                i += strlen((((*array_of_reg_exp_tav)[j]).regular_exp).round_brackets_tav.str2);
                i += 3;
                j++;
                if(j==*size_of_array_of_reg_exp_tav) break;

            }
                // put [x-y] into array
            set_arr_of_reg_exp_tav_square_bracket(array_of_reg_exp_tav, temp_pattern, j,i);
             if((((*array_of_reg_exp_tav)[j]).type_of_regular_exp).is_square_brackets ==1) {
                i += 4;
                j++;
                if(j==*size_of_array_of_reg_exp_tav) break;


             }


                //put point into array
            else if ((temp_pattern[i] == 0x2e) && (temp_pattern[i - 1] != 0x5c)) { // Ascii for '.' is 2e
                (((*array_of_reg_exp_tav)[j]).regular_exp).point_tav.initialize_point=1;
                 (((*array_of_reg_exp_tav)[j]).type_of_regular_exp).is_point=1;
                j++;
                 if(j==*size_of_array_of_reg_exp_tav) break;



             }

                //skip '\'
            else if(temp_pattern[i] == 0x5c){
                continue;
            }

                //put normal_tav into array
            else{
                ((*array_of_reg_exp_tav)[j]).regular_exp.normal_tav=temp_pattern[i];
                 ((*array_of_reg_exp_tav)[j]).type_of_regular_exp.is_normal_tav=1;
                j++;
                 if(j==*size_of_array_of_reg_exp_tav) break;



             }


        }

    }

}
