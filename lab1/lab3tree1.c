#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>

int main(){
    pid_t process_id;
    process_id = fork();
    int i=1;
    if(process_id ==0 ){
        printf("I am from child process %d, having pid: %d and ppid: %d \n",i, getpid(),getppid());
        i++;
        process_id = fork();
        if (process_id ==0)
        {
            printf("I am from child process %d, having pid: %d and ppid: %d \n",i, getpid(),getppid());
            i++;
            process_id = fork();
            if (process_id ==0)
            {
                printf("I am from child process %d, having pid: %d and ppid: %d \n",i, getpid(),getppid());
                
            }
        }
    }
    return 0;
}