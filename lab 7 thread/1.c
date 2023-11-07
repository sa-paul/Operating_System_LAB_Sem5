// 1. Create a Single Thread:
#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("This is a single thread.\n");
    pthread_exit(NULL);
}
int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, NULL);
    pthread_join(thread, NULL);
    return 0;
}
