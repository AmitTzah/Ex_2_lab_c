#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    char *current_line = NULL;
    size_t n;

    FILE *fptr= fopen(argv[2], "r");

    if (fptr ==NULL)
        return 1;
    while(getline(&current_line, &n, fptr) != EOF){
        if (strstr(current_line, argv[1]) != NULL)
            printf("%s", current_line);
    }
    free(current_line);
    fclose(fptr);

    return 0;
}
