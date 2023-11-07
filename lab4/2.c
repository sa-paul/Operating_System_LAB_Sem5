// p0 is child of p1 and p1 is child of p2 and ... and p n-1 is child of pn process
// print them in consecutive reverse order n n-1 .. 4 3 2 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    int n;
    printf("Enter no of process: ");
    scanf("%d",&n);

    // creating n+1 array to store pids
    pid_t childs[n+1];
    for (int i = 0; i < n; i++)
    {   
        // parents create its child
        childs[i+1]=fork();
        if(childs[i+1]>0){
            // parent waits for its child
            waitpid(childs[i+1],NULL,0);
            // parent prints its content after child has done
            printf("%d\n", i+1);
            // parent exits
            exit(0);
        }
    }
    return 0;
}