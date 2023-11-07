#include<iostream>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

using namespace std;

bool search(const int * arr, int n , int target)
{
    for (int i = 0; i < n; i++)
    {
        if(arr[i]==target) return true;
    }
    return false;
}

int main(void){
    int n = 1e4, m = 2, target = 100;
    srand(time(0));
    int arr[n+1];
    clock_t startTime, endTime;
    double duration;

    for (int i = 0; i < n+1; i++)
    {
        arr[i] = (rand()%1001);
    }

    printf("Enter the number of childs: ");
    scanf("%d",&m);
    printf("Enter Target Number: ");
    scanf("%d",&target);


    startTime = clock();
    pid_t pid[m];
    for (int i = 0; i < m; i++)
    {
        pid_t p = fork();
        if (p==0)
        {
            pid[i] = p;
            bool st = search(arr+(i*(n/m)), n/m, target);
            if(st) return 0;
            else return 1;
        }
    }
    
    endTime = clock();
    duration = (double)(endTime-startTime)/ (double)(CLOCKS_PER_SEC);
    cout<<"Time Consumed: "<<duration<<endl;

    for (int  i = 0; i < m; i++)
    {
        int status;
        wait(&status);
        if(!status){
            cout<<"Found"<<endl;
            return 0;
        }
    }
    cout<<"NOT Found"<<endl;

    return 0;
}