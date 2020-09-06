#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("Parent before Sleep \n");
    pid_t child_pid;

    child_pid = fork();
    if (child_pid > 0)
    {

        sleep(6);
        printf("Parent process is converted into Zombie process \n ");
    }
    else
    {
        exit(0);
    }
    return 0;
}