#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<time.h>

#define N 10000
#define SEARCH_RANGE 1000

int arr[N];

void child_handler(int sig) {
    printf("Child process found the target and will terminate.\n");
    exit(0);
}

int main() {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < N; i++) {
        arr[i] = rand() % SEARCH_RANGE + 1;
    }

    int x;
    printf("Enter the integer to search (1-1000): ");
    scanf("%d", &x);

    int r;
    pid_t child_pid[2];

    for (r = 0; r < 2; r++) {
        child_pid[r] = fork();

        if (child_pid[r] == 0) {
            signal(SIGUSR1, child_handler);
            break;
        }
    }

    if (r == 2) {
        int lower = (r == 0) ? 0 : N / 2;
        int upper = (r == 0) ? N / 2 : N;

        for (int i = lower; i < upper; i++) {
            if (arr[i] == x) {
                printf("Child %d found the target %d at index %d.\n", r + 1, x, i);
                kill(getppid(), SIGUSR1); // Notify parent
                exit(0);
            }
        }
        exit(1); // Target not found
    } else if (r == 0) {
        waitpid(child_pid[0], NULL, 0);
        printf("Child 1 terminated.\n");
        kill(child_pid[1], SIGTERM); // Terminate second child
    } else if (r == 1) {
        waitpid(child_pid[1], NULL, 0);
        printf("Child 2 terminated.\n");
        kill(child_pid[0], SIGTERM); // Terminate first child
    }

    return 0;
}