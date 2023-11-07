// 3. Create Three Threads:
#include <stdio.h>
#include <pthread.h>
int i=0;
void *threadFunction(void *arg) {
    printf("This is a %d thread.\n",i++);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread[3];
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&thread[i], NULL, threadFunction, NULL);
    }
    
    // pthread_create(&thread2, NULL, threadFunction, NULL);
    // pthread_create(&thread3, NULL, threadFunction, NULL);
    for (int i = 0; i < 3; i++)
    {
        pthread_join(thread[i], NULL);
    }
    
    // pthread_join(thread2, NULL);
    // pthread_join(thread3, NULL);
    return 0;
}
