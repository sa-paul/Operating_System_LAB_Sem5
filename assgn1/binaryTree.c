#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

void log_pid_ppid(int pid, int ppid, FILE* log_file) {
    time_t now = time(0);
    char* dt = ctime(&now);
    fprintf(log_file, "PID: %d, PPID: %d, Timestamp: %s", pid, ppid, dt);
    printf("PID: %d, PPID: %d\n", pid, ppid);
}

void create_tree(int depth, int pid, FILE* log_file) {
    if (depth == 0) {
        log_pid_ppid(getpid(), pid, log_file);
        sleep(20);
        return;
    }

    pid_t left_child_pid, right_child_pid;
    left_child_pid = fork();

    if (left_child_pid == -1) {
        perror("Error: fork failed");
        return;
    } else if (left_child_pid == 0) {
        // left child process
        log_pid_ppid(getpid(), getppid(), log_file);
        create_tree(depth - 1, getpid(), log_file);
        return;
    } else {
        // parent process
        right_child_pid = fork();

        if (right_child_pid == -1) {
            perror("Error: fork failed");
            return;
        } else if (right_child_pid == 0) {
            // right child process
            log_pid_ppid(getpid(), getppid(), log_file);
            create_tree(depth - 1, getpid(), log_file);
            return;
        } else {
            // parent process
            log_pid_ppid(getpid(), pid, log_file);
            wait(NULL);
            wait(NULL);
        }
    }
}

int main() {
    int n;
    printf("Enter the depth of the full binary tree: ");
    scanf("%d", &n);

    int num_nodes = pow(2, n) - 1;
    printf("The number of nodes will be: %d\n", num_nodes);

    FILE* log_file = fopen("log1.txt", "w");
    if (!log_file) {
        perror("Error: could not open log file");
        return 1;
    }

    create_tree(n, getpid(), log_file);
    fclose(log_file);

    return 0;
}
