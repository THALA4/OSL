#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // argc should be greater than 1 since the first argument is the program name
    if (argc < 2) {
        printf("No elements to display.\n");
        return 1;
    }

    printf("Array in Reverse Order:\n");
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]); // Display arguments in reverse order
    }
    printf("\n");

    return 0;
}
