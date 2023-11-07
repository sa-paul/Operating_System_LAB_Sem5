// p0 is child of p1 and p2 like complete tree upto level 2
// print inorder traversal
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>

#define N 7
pid_t childs[N + 1];
void inorder(int i)
{   
    // base case
    if (i >= N)
    {
        exit(0);
    }

    // creating left child using fork
    pid_t leftChild = fork();
    // calling inorder for left child
    if (leftChild == 0)
    {
        inorder(2 * i + 1);
    }
    else
    {   
        // parent wait for left child to finish
        waitpid(leftChild, NULL, 0);
        // parent prints its content
        printf("%c\n", 'a' + i);

        // parent creating right child using fork
        pid_t rightChild = fork();
        // calling inorder for right child
        if (rightChild == 0)
        {
            inorder((2 * i + 2));
        }
        else
        {   
            // parent waiting for its right child
            waitpid(rightChild, NULL, 0);
        }
        exit(0);
    }
}

int main()
{
    inorder(0);
    return 0;
}