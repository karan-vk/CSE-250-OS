#include <stdio.h>
int available[10];
int allocate[10][10];
int request[10][10];
int needed[10][10];

int numberOfProcesses, numberOfResources;

void input();
void show();
void compute();


int main()
{
    printf("Deadlock Detection Algorithm\n");
    input();
    show();
    compute();
    return 0;
}
void input()
{
    int i, j;
    printf("Enter the number of Processes:\t");
    scanf("%d", &numberOfProcesses);
    printf("Enter the number of Resource Instances:\t");
    scanf("%d",&numberOfResources);
    printf("Enter the Request Matrix:\n");
    for( i = 0; i < numberOfProcesses; i++)
    {
        printf("process %d:\n", i);
        for(j = 0; j < numberOfResources; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }
    printf("Enter the Allocation Maxtrix:\n");
    for(i = 0; i < numberOfProcesses; i++)
    {
        printf("process %d:\n", i);
        for (j = 0; j < numberOfResources; j++)
        {
            scanf("%d", &allocate[i][j]);
        }
    }
    printf("Enter the available Resources:\n");
    for(j = 0; j < numberOfResources; j++)
    {
        scanf("%d", &available[j]);
    }
}

void show()
{
    int i, j;
    printf("Process\t Allocation\t Request\t Available\t ");
    
    for(i = 0; i < numberOfProcesses; i++)
    {
        printf("\nP%d\t", i+1);
        
        for(j = 0; j < numberOfResources; j++)
        {
            printf("%d ", allocate[i][j]);
        }
        printf("\t ");
        
        for(j = 0; j < numberOfResources; j++)
        {
            printf("%d ", request[i][j]);
        }
        printf("\t");
        
        if (i == 0) {
            for (j = 0; j < numberOfResources; j++)
            {
                printf("%d ", available[j]);
            }
        }
    }
}

void compute()
{
    int finish[10], needed[10][10], flag = 1, k;
    int dead[10];
    int i, j;
    for( i = 0; i < numberOfProcesses; i ++ )
    {
        finish[i]=0;
    }
    for(i = 0; i < numberOfProcesses; i++)
    {
        for(j = 0; j < numberOfResources; j++)
        {
            needed[i][j] = request[i][j] - allocate[i][j];
        }
    }
    while(flag)
    {
        flag = 0;
        for (i = 0; i < numberOfProcesses; i++)
        {
            int c = 0;
            for( j = 0; j < numberOfResources; j++)
            {
                if ( ( finish[i] == 0 ) && ( needed[i][j] <= available[j] ) )
                {
                    c++;
                    if ( c == numberOfResources )
                    {
                        for(k = 0; k < numberOfResources; k++)
                        {
                            available[k] += allocate[i][j];
                            finish[i] = 1;
                            flag = 1;
                        }
                        if (finish[i]==1)
                        {
                            i = numberOfProcesses;
                        }
                    }
                }
            }
        }
    }
    
    j = 0;
    flag = 0;
    for(i = 0; i < numberOfProcesses; i++)
    {
        if(finish[i] == 0)
        {
            dead[j] = i;
            j++;
            flag = 1;
        }
    }
    if(flag == 1)
    {
        printf("\n\nSystem is in Deadlock and the Deadlock process are \n");
        for(i = 0; i < numberOfProcesses; i++)
        {
            printf("Process#%d\t", dead[i]);
        }
    }else{
        printf("\n No Deadlock");
    }
}