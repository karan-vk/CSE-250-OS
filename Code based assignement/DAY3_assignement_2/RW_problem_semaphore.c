#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>


/* define # readers */
#define THREADCOUNT 10

void *reader(void *);
void *writer(void *);

void databaseAccess();
void databaseNonAccess();

sem_t sem;
int rCount = 0; //Read Count
int wCount = 0; //Write Count
int reqWrite = 0; //Request Write

int main()
{
    pthread_t readers[THREADCOUNT], writerThead;
    int i;
    int ids[THREADCOUNT];
    sem_init(&sem, 0, 1);
    for (i = 0; i < THREADCOUNT; i++)
    {
        ids[i] = i + 1;
        if (pthread_create(&readers[i], 0, reader, &ids[i]) != 0)
        {
            perror("error creating reader thread");
            //exit(1);
        }
    }
    if (pthread_create(&writerThead, 0, writer, 0) != 0)
    {
        perror("error creating writer thread");
        //exit(1);
    }

    pthread_join(writerThead, 0);
    sem_destroy(&sem);
    return 0;
}

void *writer(void *arg)
{
    int wrt;
    while (1)
    {
        wrt = 1;
        databaseNonAccess();

        sem_wait(&sem);
        if (rCount == 0)
            wCount++;
        else
        {
            wrt = 0;
            reqWrite = 1;
        }
        sem_post(&sem);

        if (wrt)
        {
            databaseAccess();
            printf("Writer writing with %d readers reading \n", rCount);

            sleep(1);

            sem_wait(&sem);
            wCount--;
            reqWrite = 0;
            sem_post(&sem);
        }

        sched_yield();
    }
    return 0;
}

void *reader(void *arg) 
{
    int i = *(int *)arg;
    int can_read;
    while (1)
    {
        can_read = 1;

        sem_wait(&sem);
        if (wCount == 0 && reqWrite == 0)
            rCount++;
        else
            can_read = 0;
        sem_post(&sem);

        if (can_read)
        {
            databaseAccess();
            printf("Thread %d reading\n", i);
            sleep(i); 

            sem_wait(&sem);
            rCount--;
            sem_post(&sem);
        }

        sched_yield();
    }
    return 0;
};
void databaseNonAccess(){};
void databaseAccess(){};
