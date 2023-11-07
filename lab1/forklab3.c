#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>

int main(){
    pid_t process_id;
    process_id = fork();
    if(process_id ==0 ){
        printf("I am from child process, having pid: %d and ppid: %d \n", getpid(),getppid());     // child block
    }
    else
    {
        printf("I am from parent process, having ppid: %d and parent ppid: %d \n\n", getpid(),getppid());     // parent block
    }
}