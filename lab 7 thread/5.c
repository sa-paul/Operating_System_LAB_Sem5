// 5. Demonstrate Use of Global and Local Variables in Threads:
#include <stdio.h>
#include <pthread.h>

int globalVariable = 0; // Global variable

void *threadFunction(void *arg) {
    int localVariable = 0; // Local variable
    globalVariable++;
    localVariable++;
    printf("Global Variable: %d, Local Variable: %d\n", globalVariable, localVariable);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, NULL);
    pthread_join(thread, NULL);
    return 0;
}
