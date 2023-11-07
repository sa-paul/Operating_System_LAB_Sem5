#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void log_pid_ppid(int pid, int ppid, FILE* log_file) {
    time_t now = time(0);
    char* dt = ctime(&now);
    fprintf(log_file, "PID: %d, PPID: %d, Timestamp: %s", pid, ppid, dt);
    printf("PID: %d, PPID: %d\n", pid, ppid);
}

int main() {
    int n;
    printf("Enter the number of child processes you want to create: ");
    scanf("%d", &n);

    FILE* log_file = fopen("log.txt", "w");
    if (!log_file) {
        perror("Error: Couldn't open the log file");
        return 1;
    }
    
    fprintf(log_file, "Parent process created\n");

    pid_t pid;
    for (int i = 0; i < n; i++) {
        pid = fork();
        if (pid == -1) {
            printf("Error in creating child process\n");
            return 1;
        } else if (pid == 0) {
            log_pid_ppid(getpid(), getppid(), log_file);
            sleep(60);
            return 0;
        } else {
            log_pid_ppid(getpid(), getppid(), log_file);
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    fclose(log_file);
    return 0;
}
