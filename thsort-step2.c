// PID: 730761368
// I pledge the COMP211 honor code.

#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 128

char *readline();


char *readline() {
    char *buffer = malloc(LINE_BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    if (fgets(buffer, LINE_BUFFER_SIZE, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

int main() {
    char *buffer;
    printf("Enter a string: ");

    while ((buffer = readline()) != NULL) {
        printf("You entered: %s", buffer);
        printf("Enter a string: ");
        free(buffer);
    }

    return 0;
}