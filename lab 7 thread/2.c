// 2. Create Two Threads:
#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("This is a thread.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, threadFunction, NULL);
    pthread_create(&thread2, NULL, threadFunction, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
