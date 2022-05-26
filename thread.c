#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>
int thread_no=0;
#define THREADMAX 100
#define SIZE 1000000000
int Array[SIZE];
int max_sum[THREADMAX];
pthread_mutex_t lock;
void* foo(void* dio);
int main(){
    srand(time(NULL));
    for(int i=0;i<SIZE;i++) Array[i]=rand()%1000;
    for(int i=0;i<THREADMAX;i++) max_sum[i]=0;
    pthread_t tids[THREADMAX];
    for(int i=0;i<THREADMAX;i++) pthread_create(&tids[i],NULL,&foo,NULL);
    for(int i=0;i<THREADMAX;i++) pthread_join(tids[i],NULL);
    long long val=0;
    for(int i=0;i<THREADMAX;i++) val+=max_sum[i];    
    printf("%lld \n",val);
}
void* foo(void* dio){
    pthread_mutex_lock(&lock);
	int thread_id = thread_no; thread_no++; 
	for (int i = thread_id*(SIZE/THREADMAX); i < (thread_id+1)*(SIZE/THREADMAX); i++) { 
        max_sum[thread_id]+=Array[i];
	} 
    pthread_mutex_unlock(&lock); 
}