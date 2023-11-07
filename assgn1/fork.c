#include<stdio.h>
// #include<sys/types.h>
#include<unistd.h>

int main() {
    int i=0;
    fork();
    fork();
    printf("Sayan Paul %d\n",++i);
    return 0;
}