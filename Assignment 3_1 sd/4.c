#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigchld_handler(int signo) {
    pid_t terminatedChild;
    int status;
    
    // Wait for any child process to exit
    while ((terminatedChild = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Child Process %d exited with status: %d\n", terminatedChild, status);
    }
}

int main() {
    pid_t childPid;

    // Set up signal handler for SIGCHLD
    signal(SIGCHLD, sigchld_handler);

    // Fork a child process
    if ((childPid = fork()) < 0) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {
        // Child process
        printf("Child Process ID: %d\n", getpid());
        // sleep(2); // Simulating some work in child process
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent Process ID: %d\n", getpid());

        // Parent process continues its work while handling SIGCHLD asynchronously
        int t=5;
        while(t--) {
            // Parent process doing some work
            // sleep(1);
            wait4(childPid,NULL,0,NULL);
            printf("Parent Process is working...\n");

            // Parent process continues its work while handling SIGCHLD
        }
    }

    return 0;
}

