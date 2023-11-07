
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

bool is_prime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int x, y;
    printf("Enter the range [x, y] (both > 1000): ");
    scanf("%d %d", &x, &y);

    if (x <= 1000 || y <= 1000)
    {
        printf("Both x and y must be greater than 1000.\n");
        return 1;
    }

    FILE *prime_file = fopen("prime_numbers.txt", "w");
    if (prime_file == NULL)
    {
        perror("Error creating prime_numbers.txt");
        return 1;
    }

    int num_children = y - x + 1;
    for (int i = 0; i < num_children; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            // Child process
            for (int num = x + i; num <= y; num += num_children)
            {
                if (is_prime(num))
                {
                    fprintf(prime_file, "%d\n", num);
                }
            }
            fclose(prime_file);
            exit(0);
        }
        else if (pid < 0)
        {
            perror("Fork failed");
        }
    }

    // Parent process waits for all child processes to complete
    for (int i = 0; i < num_children; i++)
    {
        wait(NULL);
    }

    fclose(prime_file);
    printf("Prime numbers written to prime_numbers.txt.\n");

    return 0;
}