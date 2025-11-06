// PID: 730761368
// I pledge the COMP211 honor code.

#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 128
#define NUM_LINES_BUFFER_SIZE 5

char *readline(void);
char **readlines(int *num_lines);
void printlines(char **lines, int num_lines);
void freelines(char **lines, int num_lines);

char *readline(void) {
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

char **readlines(int *num_lines) {
    char **lines = malloc(NUM_LINES_BUFFER_SIZE * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    *num_lines = 0;
    char *line;

    while ((line = readline()) != NULL && *num_lines < NUM_LINES_BUFFER_SIZE) {
        lines[*num_lines] = line;
        (*num_lines)++;
    }

    return lines;
}

void printlines(char **lines, int num_lines) {
    for (int i = 0; i < num_lines; i++) {
        printf("%s", lines[i]);
    }
}

void freelines(char **lines, int num_lines) {
    for (int i = 0; i < num_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}


int main(void) {
    int num_lines = 0;
    char **lines = readlines(&num_lines);

    printlines(lines, num_lines);
    freelines(lines, num_lines);

    return 0;
}
