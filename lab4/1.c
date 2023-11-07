// p0 is direct child to p1 p2 .. pn process
// print content of them in order as abcdef...z
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    int n;
    scanf("%d",&n);
    // array to store childs
    pid_t childs[n];
    for (int i = 0; i < n; i++)
    {   
        // parent creates childs
        childs[i]=fork();
        if(childs[i]==0){
            if (i>0)
            {   
                // parent waits for its consecutive childs
                waitpid(childs[i-1],NULL,0);
            }
            // child prints its content
            printf("%c", 'a'+i);
            // child exits
            exit(0);
        }
    }
    // parent waits for its last child
    waitpid(childs[n-1],NULL,0);
    printf("\n");
    return 0;
}