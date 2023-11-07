#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void logid(int, int, FILE *);


int main() 
{
    int n;
    scanf("%d", &n);
    FILE *fout = fopen("./log.txt", "w");
    if(fout == NULL) exit(1);

    logid(getpid(), getppid(), fout);

    for(int i=0; i<n; i++) 
    {
        pid_t p = fork();
        if(p == 0) {
            //child
            logid(getpid(), getppid(), fout);
        }
        else {
            wait(NULL);
            fclose(fout);
            return 0;
        }
    }
    

    return 0;
}


void logid(int pid, int ppid, FILE *fout) {
    fprintf(fout, "process with PID %d and PPID %d\n", pid, ppid);
    fflush(fout);
}