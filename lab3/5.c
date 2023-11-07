#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include <math.h>

int r1, r2, r3, r4; // Ranges for child processes
volatile int complete = 0; // Indicates how many child processes have completed

void sigusr1_handler(int signum) {
    complete++;
    signal(SIGUSR1, sigusr1_handler);
}

void sigusr2_handler(int signum) {
    complete++;
    signal(SIGUSR2, sigusr2_handler);
}

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

void child_process(int start, int end) {
    FILE *prime_file = fopen("prime.txt", "a");
    if (prime_file == NULL) {
        perror("Error opening prime.txt");
        exit(EXIT_FAILURE);
    }

    for (int num = start; num <= end; num++) {
        if (is_prime(num)) {
            fprintf(prime_file, "%d\n", num);
        }
    }

    fclose(prime_file);

    if (start == r1) {
        kill(getppid(), SIGUSR1);
    } else {
        kill(getppid(), SIGUSR2);
    }

    exit(EXIT_SUCCESS);
}

int main() {
    int x = 1; // Range start
    int y = 100; // Range end

    r1 = x;
    r2 = (x + y) / 3;
    r3 = r2 + 1;
    r4 = 2 * (x + y) / 3;

    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    pid_t child1 = fork();

    if (child1 == 0) {
        child_process(r1, r2);
    } else if (child1 > 0) {
        pid_t child2 = fork();
        if (child2 == 0) {
            child_process(r3, r4);
        } else if (child2 > 0) {
            while (complete < 2) {
                pause();
            }
            // Terminate child processes
            kill(child1, SIGTERM);
            kill(child2, SIGTERM);
            printf("Both child processes completed.\n");
        } else {
            perror("Error creating second child process");
            return 1;
        }
    } else {
        perror("Error creating first child process");
        return 1;
    }

    return 0;
}