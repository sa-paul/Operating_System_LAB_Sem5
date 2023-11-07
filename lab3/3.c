#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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

    int n;
    printf("Enter the number of child processes: ");
    scanf("%d", &n);

    pid_t child_pid[n];
    clock_t start_time, end_time;

    start_time = clock();

    for (int r = 0; r < n; r++) {
        child_pid[r] = fork();

        if (child_pid[r] == 0) {
            signal(SIGUSR1, child_handler);
            int lower = r * (N / n);
            int upper = (r == n - 1) ? N : (r + 1) * (N / n);

            for (int i = lower; i < upper; i++) {
                if (arr[i] == x) {
                    printf("Child %d found the target %d at index %d.\n", r + 1, x, i);
                    kill(getppid(), SIGUSR1); // Notify parent
                    exit(0);
                }
            }
            exit(1); // Target not found
        }
    }

    for (int r = 0; r < n; r++) {
        waitpid(child_pid[r], NULL, 0);
        printf("Child %d terminated.\n", r + 1);
    }

    end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", execution_time);

    return 0;
}