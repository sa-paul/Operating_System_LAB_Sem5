#include <stdio.h>     // printf scanf
#include <unistd.h>    // slepp
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // wait
#include <signal.h>    // signal kill
#include <stdlib.h>    // exit

#define MAX_PROCESS 5

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

void find_primes(int start, int end)
{
    for (int num = start; num <= end; num++)
    {
        if (is_prime(num))
        {
            printf("%d ", num);
        }
    }
}

int main()
{
    int N, M;
    printf("Enter the value of N (upper limit): ");
    scanf("%d", &N);
    printf("Enter the number of child processes (M): ");
    scanf("%d", &M);
    M = (M > MAX_PROCESS) ? MAX_PROCESS : M; // Limit M to MAX_PROCESS

    int range_size = N / M;
    int remaining = N % M;

    for (int i = 0; i < M; i++)
    {
        int start = i * range_size + 1;
        int end = start + range_size - 1 + (i == M - 1 ? remaining : 0);
        pid_t pid = fork();

        if (pid == 0)
        {
            // Child process
            printf("Child %d: Primes in range [%d, %d]: ", i + 1, start, end);
            find_primes(start, end);
            printf("\n");
            exit(0);
        }
        else if (pid < 0)
        {
            // Fork failed
            perror("Fork failed");
            exit(1);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < M; i++)
    {
        wait(NULL);
    }

    return 0;
}