#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>

int main(){
    pid_t process_id1,process_id2;
    process_id1 = fork();
    int i=1,j=1;
    if(process_id1 ==0 ){
        printf("I am from child process %d, having pid: %d and ppid: %d \n",i, getpid(),getppid());
        i++;
        process_id1 = fork();
        process_id2 = fork();
        if(process_id1 ==0 ){
            printf("I am from child process %d, having pid: %d and ppid: %d \n",i, getpid(),getppid());
            i++;
            
        }
        if(process_id2 ==0 )
        {
            printf("I am from child process %d, having pid: %d and ppid: %d \n",j, getpid(),getppid());
            j++;
        }
        
    }
    if(process_id2 ==0 )
    {
        printf("I am from child process %d, having pid: %d and ppid: %d \n",j, getpid(),getppid());
        j++;
        process_id1 = fork();
        process_id2 = fork();
        if(process_id1 ==0 ){
            printf("I am from child process %d, having pid: %d and ppid: %d \n",i, getpid(),getppid());
            i++;
            
        }
        if(process_id2 ==0 )
        {
            printf("I am from child process %d, having pid: %d and ppid: %d \n",j, getpid(),getppid());
            j++;
        }
    }
}