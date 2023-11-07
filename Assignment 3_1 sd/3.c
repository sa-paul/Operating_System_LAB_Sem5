#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t childPid;

    // Fork a child process
    if ((childPid = fork()) < 0) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {
        // Child process
        printf("Child Process ID: %d\n", getpid());

        // Execute "ls -l /home"
        execl("/bin/ls", "ls", "-l", "/home", (char *)NULL);
        perror("Exec error");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent Process ID: %d\n", getpid());

        // Wait for the child process to exit
        int status;
        wait(&status);
        printf("Child Process %d exited with status: %d\n", childPid, status);
        





        
        // Demonstrate differences between wait() and wait4()
        for (int i = 0; i < 3; ++i) {
            if ((childPid = fork()) < 0) {
                perror("Fork error");
                exit(EXIT_FAILURE);
            }
            
            if (childPid == 0) {
                // Child process
                printf("Child Process ID: %d\n", getpid());
                sleep(2); // Child processes sleep for 2 seconds before exiting
                exit(EXIT_SUCCESS);
            }
        }

        // Parent process waiting for multiple children with asynchronous exit timings
        for (int i = 0; i < 3; ++i) {
            pid_t terminatedChild = wait(NULL);
            printf("Child Process %d exited\n", terminatedChild);
        }
    }

    return 0;
}
