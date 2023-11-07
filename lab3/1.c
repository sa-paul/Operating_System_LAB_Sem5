#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

FILE *logFile;

void sigintHandler(int signum) {
    fprintf(logFile, "Received Ctrl+C. Terminating all child processes.\n");
    fclose(logFile);
    exit(0);
}

void createChildProcesses(int n) {
    pid_t parentPid = getpid();
    fprintf(logFile, "Parent Process: PID=%d, PPID=%d\n", parentPid, getppid());

    for (int i = 1; i <= n; i++) {
        pid_t childPid = fork();
        
        if (childPid == -1) {
            perror("Error while fork");
            exit(1);
        } else if (childPid == 0) {
            fprintf(logFile, "Child Process: PID=%d, PPID=%d\n", getpid(), getppid());
            fclose(logFile);
            break; // Child process breaks out of the loop
        }
        
        // Only the parent continues in the loop
        fprintf(logFile, "Parent Process: Created child %d with PID=%d\n", i, childPid);
    }
}

int main() {
    signal(SIGINT, sigintHandler); // Register Ctrl+C signal handler

    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    logFile = fopen("log3.txt", "a");
    if (logFile == NULL) {
        perror("fopen");
        return 1;
    }

    createChildProcesses(n);

    // All processes enter a loop
    while (1) {
        sleep(1);
    }

    return 0;
}