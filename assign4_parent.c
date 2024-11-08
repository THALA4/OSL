/* parent.c - Parent process that sorts an array and passes it to child process */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Implements bubble sort algorithm to sort an integer array
 * @param arr The array to be sorted
 * @param n Length of the array
 */
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // Compare adjacent elements and swap if they are in wrong order
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/**
 * Utility function to display array elements
 * @param arr Array to be displayed
 * @param n Length of the array
 */
void displayArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n;

    // Get array size from user
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Declare array of size n
    int arr[n];

    // Get array elements from user
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Sort the array using bubble sort
    bubbleSort(arr, n);
    printf("Parent sorted the array: ");
    displayArr(arr, n);

    // Create child process
    int pid = fork();

    // Check if fork failed
    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {   // Child Process
        // Prepare arguments for child program
        // char *args[n + 2];  // +2 for program name and NULL terminator
        // args[0] = "./child"; // First argument is the program name

        // // Convert integers to strings for passing as arguments
        // for (int i = 0; i < n; i++) {
        //     char *arg = malloc(10); // Allocate memory for string representation
        //     sprintf(arg, "%d", arr[i]);
        //     args[i + 1] = arg;
        // }
        // args[n + 1] = NULL; // NULL terminate the arguments array

        char *args[n + 2];     // +1 for program name, +1 for NULL terminator
        args[0] = "./child"; // Name of the program to execute
        for (int i = 0; i < n; i++)
        {
            args[i + 1] = malloc(10);           // Allocate space for each argument
            sprintf(args[i + 1], "%d", arr[i]); // Convert int to string
        }
        args[n + 1] = NULL; // Null-terminate the arguments

        // Execute child program
        if (execve(args[0], args, NULL) < 0)
        {
            perror("execve failed");
            return 1;
        }
    }
    else
    { // Parent Process
        // Wait for child process to complete
        wait(NULL);
    }

    return 0;
}