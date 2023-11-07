#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main()
{
    printf("\n\t+++ Inside main()\n");

    pid_t pid;
    pid = fork();   // Fork a new process
    if (pid < 0)    // Fork failed
    {
        perror("fork"); exit(1);
    }
    else if (pid == 0)   // Child process
    {   
        printf("\n\t+++ Inside Child\n");
        
        char * argv[]={"ls","-l",".",NULL};
        // Executing the `ls -l` command
        execv("/bin/ls",argv);
        
        // char * argv[]={NULL};
        // // Executing the `ls -l` command
        // execv("./test",argv);

        // If fails, this code will not be executed
        perror("execv failed");
        exit(0);
    }
    else    // Parent process
    {
        wait(NULL);     // Wait for the child process to finish
        printf("\n\t+++ Inside Parent\n");
    }
    printf("\n\t+++ Inside main() again\n");
    return 0;
}