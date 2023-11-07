#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

// Function to store pid and ppid of each process
void loginfo(pid_t pid, pid_t ppid, int i)
{
    FILE *fp;
    fp = fopen("log2.txt", "a");
    time_t t = time(0);
    if (fp != NULL)
    {
        fprintf(fp, "Child process %d: [pid] %d parent process [ppid] %d [time] %s", i + 1, pid, ppid, ctime(&t));
        fclose(fp);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes ");
    scanf("%d", &n);
    pid_t pid;
    printf("Parent process id %d and ppid %d", getpid(), getppid());
    printf("\n");
    fflush(__stdoutp);

    FILE *fp;
    fp = fopen("log2.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "Parent Process: [pid] %d [ppid] %d \n", getpid(), getppid());
        fclose(fp);
    }
    for (int i = 0; i < n; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("Child process %d: [pid] %d parent process [ppid] %d \n", i, getpid(), getppid());
            loginfo(getpid(), getppid(), i);
            continue;
        }
        else if (pid < 0)
        {
            exit(0);
        }
        else
        {
            sleep(1);
            exit(0);
        }
    }

    for (int i = 0; i < n; i++)
        wait(NULL);
    return 0;
}