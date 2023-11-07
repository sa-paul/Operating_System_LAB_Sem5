#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

int is_prime(int num) {
    if (num <= 1)
        return 0;
    if (num <= 3)
        return 1;
    if (num % 2 == 0 || num % 3 == 0)
        return 0;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    }

    return 1;
}

void child_handler(int sig) {
    // Do nothing, just handle the signal
}

int main() {
    int x, y;
    printf("Enter the range [x, y] (both > 10000): ");
    scanf("%d %d", &x, &y);

    if (x > y || x <= 10000 || y <= 10000) {
        printf("Invalid range.\n");
        return 1;
    }

    int mid = (x + y) / 2;

    pid_t child_pid[2];

    child_pid[0] = fork();

    if (child_pid[0] == 0) {
        signal(SIGUSR1, child_handler);

        for (int num = x; num <= mid; num++) {
            if (is_prime(num)) {
                printf("Child 1 found prime number: %d\n", num);
                kill(getppid(), SIGUSR1); // Notify parent
            }
        }

        exit(0);
    } else {
        child_pid[1] = fork();

        if (child_pid[1] == 0) {
            signal(SIGUSR1, child_handler);

            for (int num = mid + 1; num <= y; num++) {
                if (is_prime(num)) {
                    printf("Child 2 found prime number: %d\n", num);
                    kill(getppid(), SIGUSR1); // Notify parent
                }
            }

            exit(0);
        } else {
            // Parent process
            pause(); // Suspend the parent process

            // Terminate child processes
            kill(child_pid[0], SIGTERM);
            kill(child_pid[1], SIGTERM);

            printf("Parent terminated child processes.\n");
        }
    }

    return 0;
}