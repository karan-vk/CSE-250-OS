#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
//this is a test for github

/* define # readers */
#define THREADCOUNT 10

void *reader(void *);
void *writer(void *);

/* Mock Functions  for future use */
void databaseAccess();
void databaseNonAccess();

/* define semaphore object */
sem_t sem;
/* number of readers reading*/
int readCount = 0;
int writeCount = 0;
int requestWrite = 0;

int main()
{
    pthread_t readers[THREADCOUNT], writerThead;
    int i;
    int ids[THREADCOUNT];
    sem_init(&sem, 0, 1);
    for (i = 0; i < THREADCOUNT; i++)
    {
        ids[i] = i + 1;
        /* create reader thread and check if error */
        if (pthread_create(&readers[i], 0, reader, &ids[i]) != 0)
        {
            perror("error creating reader thread");
            //exit(1);
        }
    }
    /* create writer thread and check if error */
    if (pthread_create(&writerThead, 0, writer, 0) != 0)
    {
        perror("error creating writer thread");
        //exit(1);
    }

    pthread_join(writerThead, 0);
    sem_destroy(&sem);
    return 0;
}

//writer method
void *writer(void *arg)
{
    // writer can now write
    int wrt;
    while (1)
    {
        wrt = 1;
        databaseNonAccess();

        sem_wait(&sem);
        if (readCount == 0)
            writeCount++;
        else
        {
            wrt = 0;
            requestWrite = 1;
        }
        sem_post(&sem);

        if (wrt)
        {
            databaseAccess();
            printf("Writer writing with %d readers reading \n", readCount);

            sleep(1);

            sem_wait(&sem);
            writeCount--;
            requestWrite = 0;
            sem_post(&sem);
        }

        sched_yield();
    }
    return 0;
}

void *reader(void *arg) /* readers function to read */
{
    int i = *(int *)arg;
    int can_read;
    while (1)
    {
        can_read = 1;

        sem_wait(&sem);
        if (writeCount == 0 && requestWrite == 0)
            readCount++;
        else
            can_read = 0;
        sem_post(&sem);

        if (can_read)
        {
            databaseAccess();
            printf("Thread %d reading\n", i);
            sleep(i); // slow it down to display

            sem_wait(&sem);
            readCount--;
            sem_post(&sem);
        }

        sched_yield();
    }
    return 0;
};