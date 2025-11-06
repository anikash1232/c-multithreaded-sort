// PID: 730761368
// I pledge the COMP211 honor code.

#include <stdio.h>
#include <stdlib.h>
#define LINE_BUFFER_SIZE 128

int main() {

    char* buffer = (char*)malloc (LINE_BUFFER_SIZE);
    printf("Enter a string: ");

    if (buffer == NULL){
        printf("out of memory\n");
        return 1;
    }

    else{

        if (fgets(buffer, LINE_BUFFER_SIZE, stdin) != NULL) {
        printf("You entered: %s", buffer);
    }

    else {
        printf("No input or error occurred.\n");
    }

    }

free(buffer);
return 0;

}