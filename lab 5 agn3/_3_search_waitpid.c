#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ARRAY_SIZE 40  // Adjust this to your desired array size
#define NUM_CHILDREN 4 // Number of child processes

int array[ARRAY_SIZE];

int search(int start, int end, int target)
{
    for (int i = start; i < end; i++)
    {
        if (array[i] == target)
        {
            return 1; // Element found
        }
    }
    return 0; // Element not found
}

int main()
{
    // Initialize the array with random integers (for demonstration purposes)
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % 1000;
        printf("%d\n", array[i]);
    }

    int target;
    printf("Enter the element to be searched: ");
    scanf("%d", &target);

    int segment_size = ARRAY_SIZE / NUM_CHILDREN;
    int start = 0;
    int end = segment_size;

    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            // Child process
            int result = search(start, end, target);
            if (result == 1)
            {
                exit(1); // Found the element, exit with status code 1
            }
            exit(0); // Element not found in this segment
        }
        else if (pid < 0)
        {
            perror("Fork failed");
        }
        else
        {
            // Parent process
            start = end;
            end += segment_size;
        }
    }

    // Parent process waits for any child to complete
    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        int status;
        pid_t child_pid = waitpid(-1,&status,0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            printf("Element found by child process with PID %d\n", child_pid);
            return 0;
        }
    }

    printf("Target NOT found!!\n");
    return 0;
}