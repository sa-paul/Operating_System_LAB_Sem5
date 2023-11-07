// 4. Create Thread within the Thread:
#include <stdio.h>
#include <pthread.h>

void *innerThreadFunction(void *arg) {
    printf("Inner thread executed.\n");
    pthread_exit(NULL);
}
void *threadFunction(void *arg) {
    pthread_t innerThread;
    pthread_create(&innerThread, NULL, innerThreadFunction, NULL);
    pthread_join(innerThread, NULL);
    printf("Thread within the thread executed.\n");
    pthread_exit(NULL);
}


int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, NULL);
    pthread_join(thread, NULL);
    return 0;
}
