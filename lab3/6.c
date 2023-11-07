#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Child process function
void child_process(int start, int end) {
    FILE *temp_file = fopen("temp_prime.txt", "w");
    if (temp_file == NULL) {
        perror("Error opening temp file");
        exit(EXIT_FAILURE);
    }

    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            fprintf(temp_file, "%d\n", i);
        }
    }

    fclose(temp_file);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s p x y\n", argv[0]);
        return 1;
    }

    int p = atoi(argv[1]);
    int x = atoi(argv[2]);
    int y = atoi(argv[3]);

    // Calculate the range for each child process
    int range = (y - x + 1) / 2;

    for (int i = 0; i < 2; i++) {
        pid_t child_pid = fork();
        if (child_pid == 0) {
            // Child process
            int start = x + i * range;
            int end = start + range - 1;
            child_process(start, end);
        } else if (child_pid < 0) {
            perror("Fork failed");
            return 1;
        }
    }

    // Wait for both child processes to finish
    int status;
    for (int i = 0; i < 2; i++) {
        wait(&status);
    }

    // Combine results from temporary files into 'prime.txt'
    FILE *prime_file = fopen("prime.txt", "a ");
    if (prime_file == NULL) {
        perror("Error opening prime file");
        return 1;
    }

    for (int i = 0; i < 2; i++) {
        FILE *temp_file = fopen("temp_prime.txt", "r");
        if (temp_file == NULL) {
            perror("Error opening temp file");
            return 1;
        }

        char c;
        while ((c = fgetc(temp_file)) != EOF) {
            fputc(c, prime_file);
        }

        fclose(temp_file);
    }

    fclose(prime_file);
    remove("temp_prime.txt");

    printf("%d prime numbers found and saved in 'prime.txt'.\n", p);

    return 0;
}