// PID: 730761368
// I pledge the COMP211 honor code.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 128

char *readline(void);
char **readlines(int *num_lines);
void printlines(char **lines, int num_lines);
void freelines(char **lines, int num_lines);
int cmp(const void *a, const void *b);


// Reads one line of arbitrary length from stdin (heap-based).
char *readline(void) {
    int capacity = INITIAL_BUFFER_SIZE;
    int length = 0;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (length + 1 >= capacity) {       // +1 for '\0'
            capacity *= 2;                  // grow buffer
            char *temp = realloc(buffer, capacity);
            if (temp == NULL) {
                fprintf(stderr, "out of memory\n");
                free(buffer);
                exit(1);
            }
            buffer = temp;
        }
        buffer[length++] = (char)c;
    }

    if (length == 0 && c == EOF) {          // nothing read
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';                  // null-terminate
    return buffer;
}


// Stores an arbitrary number of lines read via readline(). 
char **readlines(int *num_lines) {
    int capacity = 5;
    char **lines = malloc(capacity * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    *num_lines = 0;
    char *line;
    while ((line = readline()) != NULL) {
        if (*num_lines >= capacity) {
            capacity *= 2;
            char **temp = realloc(lines, capacity * sizeof(char *));
            if (temp == NULL) {
                fprintf(stderr, "out of memory\n");
                for (int i = 0; i < *num_lines; i++)
                    free(lines[i]);
                free(lines);
                exit(1);
            }
            lines = temp;
        }
        lines[*num_lines] = line;
        (*num_lines)++;
    }
    return lines;
}


int cmp(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    return strcmp(s1, s2);
}


void printlines(char **lines, int num_lines) {
    for (int i = 0; i < num_lines; i++)
        printf("%s\n", lines[i]);
}


void freelines(char **lines, int num_lines) {
    for (int i = 0; i < num_lines; i++)
        free(lines[i]);
    free(lines);
}


int main(void) {
    int num_lines = 0;
    char **lines = readlines(&num_lines);

    qsort(lines, num_lines, sizeof(char *), cmp);
    printlines(lines, num_lines);
    freelines(lines, num_lines);

    return 0;
}