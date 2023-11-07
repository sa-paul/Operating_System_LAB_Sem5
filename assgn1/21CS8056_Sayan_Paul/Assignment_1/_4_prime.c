
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

void find_primes_range(int start, int end) {
    for (int num = start; num <= end; num++) {
        if (is_prime(num)) {
            printf("%d ", num);
        }
    }
    printf("\n");
}

int main() {
    int N,M;
    printf("enter the upper limit\n");
    scanf("%d",&N);
    printf("enter the number of child process to create\n");
    scanf("%d",&M);

    int chunk_size = N / M;
    for (int i = 0; i < M; i++) {
         pid_t pid = fork();

        if (pid == 0) {  // Child process
        	printf("parent id= %d\n",getpid());
             int start = i * chunk_size + 1;
             int end = (i < M - 1) ? start + chunk_size - 1 : N;
             find_primes_range(start, end);
             exit(0);
         }
         
     }

    printf("\n");

    return 0;
}