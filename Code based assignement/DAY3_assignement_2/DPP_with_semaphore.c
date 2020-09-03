#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define MIN(a, b) (a<b?a:b)
#define MAX(a, b) (a>b?a:b)

sem_t fork[5];

void *eat(void *arg){
    int i = (int)arg;
    int count=2;
    while(count){
        sem_wait(&fork[MIN(i, (i+1)%5)]);
        sem_wait(&fork[MAX(i, (i+1)%5)]);
        printf("Philosopher %d is eating now\n", i);
        sem_post(&fork[(i+1)%5]);
        sem_post(&fork[i]);
        count--;
    }
}

int main(){
    pthread_t philosopher[5];
    int i;
    for(i=0; i<5; i++){
        sem_init(&fork[i], 0, 1);
    }
    for(i=0; i<5; i++){
        pthread_create(&philosopher[i], NULL, eat, (void*)i);
    }
    for(i=0; i<5; i++){
        pthread_join(philosopher[i], NULL);
    }
    return 0;
}