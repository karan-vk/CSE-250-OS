#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define N_PHILOSOPHERS 5
#define LEFT (ph_num + N_PHILOSOPHERS - 1) % N_PHILOSOPHERS
#define RIGHT (ph_num + 1) % N_PHILOSOPHERS

pthread_mutex_t mutex;
pthread_cond_t condition[N_PHILOSOPHERS];

enum { THINKING, HUNGRY, EATING } state[N_PHILOSOPHERS];
int phil_num[N_PHILOSOPHERS];

void *philosophing (void *arg);
void pickup_forks(int ph_num);
void return_forks(int ph_num);
void test(int ph_num);

int main(int argc, char *argv[])
{
  /* Setup */
  pthread_t ph_thread[N_PHILOSOPHERS];
  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < N_PHILOSOPHERS; i++) {
    pthread_cond_init(&condition[i], NULL);
    phil_num[i] = i;
  }

  /* Meat */
  for (int i = 0; i < N_PHILOSOPHERS; i++) {
    pthread_create(&ph_thread[i], NULL, philosophing, &phil_num[i]);
    printf("Philosopher #%d sits on the table.\n", i + 1);
    sleep(1);
  }
  for (int i = 0; i < N_PHILOSOPHERS; i++)
    pthread_join(ph_thread[i], NULL);

  /* Cleanup */
  pthread_mutex_destroy(&mutex);
  for (int i = 0; i < N_PHILOSOPHERS; i++)
    pthread_cond_destroy(&condition[i]);

  return(0);
}


void pickup_forks(int ph_num) {
  pthread_mutex_lock(&mutex);

  printf("Philosopher #%d is HUNGRY. She tries to grab her forks.\n", ph_num + 1);
  state[ph_num] = HUNGRY;
  test(ph_num);
  while (state[ph_num] != EATING) 
    pthread_cond_wait(&condition[ph_num], &mutex);

  pthread_mutex_unlock(&mutex);
}

void test(int ph_num) {
  if (state[ph_num] == HUNGRY && 
      state[LEFT] != EATING && 
      state[RIGHT] != EATING) {
    printf("Philosopher #%d starts EATING.\n", ph_num + 1);
    state[ph_num] = EATING;
    sleep(3);
    pthread_cond_signal(&condition[ph_num]);
  }
}

void return_forks(int ph_num) {
  pthread_mutex_lock(&mutex);

  printf("Philosopher #%d puts down chopsticks. Now she asks her neighbors if they are hungry.\n", ph_num + 1);
  state[ph_num] = THINKING;
  test(LEFT);
  test(RIGHT);

  pthread_mutex_unlock(&mutex);
}
void *philosophing(void *arg)
{
  while(1) {
    int *ph_num = arg;
    printf("Philosopher #%d starts thinking.\n", *ph_num + 1);
    sleep(2);
    pickup_forks(*ph_num);
    return_forks(*ph_num);
  }
}