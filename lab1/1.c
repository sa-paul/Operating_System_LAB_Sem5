// p0 is direct child to p1 p2 .. pn process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Function to store pid and ppid of each process
void loginfo(pid_t pid, pid_t ppid, int i)
{
    FILE *fp;
    fp = fopen("log.txt", "a");
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
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    pid_t pid;
    printf("Parent process pid %d and ppid %d \n", getpid(), getppid());

    FILE *fp;
    fp = fopen("log.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "Parent Process: [pid] %d [ppid] %d \n", getpid(), getppid());
        fclose(fp);
    }
    fflush(__stdoutp);
    // printf(" ");

    for (int i = 0; i < n; i++)
    {
        // pid = fork();
        if (fork() == 0)
        {
            printf("Child process %d: [pid] %d parent process [ppid] %d \n", i, getpid(), getppid());
            loginfo(getpid(), getppid(), i);
            // wait(NULL);
            exit(0);
        }
    }

    for (int i = 0; i < n; i++)
    {
        wait(NULL);
    }
    return 0;
}