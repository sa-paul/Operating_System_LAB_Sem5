// 6. Print Numbers in Different Threads:
#include <stdio.h>
#include <pthread.h>
static int k=0;
void *printNumbers(void *arg) {
    int start = *((int*)arg);
    printf("\nThread %d: ", k++);
    for (int i = start; i <= start + 9; ++i) {
        printf("%d ", i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t th[3];
    int st[3]={1,11,21};
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&th[i], NULL, printNumbers, &st[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        pthread_join(th[i], NULL);
    }
    return 0;
}
