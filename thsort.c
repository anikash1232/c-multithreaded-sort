// PID: 730761368
// I pledge the COMP211 honor code.

#include <stdio.h>
#define LINE_BUFFER_SIZE 128

int main() {

    char buffer[LINE_BUFFER_SIZE];
    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("You entered: %s", buffer);
    } 

    else {
        printf("No input or error occurred.\n");
    }

return 0;

}