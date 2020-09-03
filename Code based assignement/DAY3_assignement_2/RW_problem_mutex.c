#include <stdio.h>
// #include <conio.h>
#include <pthread.h>
#include <stdlib.h>
void *read();
void *write();
int readcount;
pthread_t thread1;
pthread_mutex_t r, w;
int main()
{
    int n1, n2, i;
    pthread_mutex_init(&r, NULL);
    pthread_mutex_init(&w, NULL);
    readcount = 0;
    printf("Enter the number of readers you want to create\n");
    scanf("%d", &n1);
    printf("Enter the number of writers you want to create\n");
    scanf("%d", &n2);
    for (i = 0; i < n1; i++)
        pthread_create(&thread1, NULL, read, NULL);
    for (i = 0; i < n2; i++)
        pthread_create(&thread1, NULL, write, NULL);
}
void *read()
{

    pthread_mutex_lock(&r);
    printf("Reading is trying to enter\n");
    readcount++;
    if (readcount == 1)
        pthread_mutex_lock(&w);
    printf("\n%d Reader is inside\n", readcount);
    pthread_mutex_unlock(&r);
    sleep(1);
    readcount--;
    pthread_mutex_lock(&r);
    if (readcount == 0)
        pthread_mutex_unlock(&w);
    pthread_mutex_unlock(&r);
    printf("reader is leaving\n");
}
void *write()
{
    printf("Writer is trying to enter\n");
    pthread_mutex_lock(&w);
    printf("Writer entered the class\n");
    sleep(1);
    pthread_mutex_unlock(&w);
    printf("writer left the class\n");
}
