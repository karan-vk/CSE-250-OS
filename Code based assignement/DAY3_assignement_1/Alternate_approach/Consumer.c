#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include "common.h"

int main(int argc, char **argv)
{
	//declaring mq and initiliasing attributes

	mqd_t mq;
	char buffer[MAX_SIZE];
	struct mq_attr attr;
	int max_vals = 1000;
	int* recvd_vals;

	//opening file in w mode and opening mq

	FILE* fp;
	fp = fopen("consumer.txt", "w");
	if (fp == NULL)
		exit(-1);

	mq = mq_open(QUEUE_NAME, O_RDONLY );
	CHECK((mqd_t) - 1 != mq);
	mq_getattr(mq, &attr);

	//allocating array for storing consumed vals

	recvd_vals = malloc (max_vals * sizeof(int));
	if (recvd_vals == NULL) {
		printf("recvd_vals malloc error\n");
		exit(1);
	}

	for (int i = 0; i < max_vals; i++)
	{
		mq_receive(mq, buffer, MAX_SIZE, NULL);//receiving msg, converting to int and storing in the array
		int received = atoi(buffer);
		recvd_vals[i] = received;
		attr.mq_curmsgs = attr.mq_curmsgs - 1;
	}

	printf("Consumer consumed:\n");

	for (int i = 0; i < max_vals; i++) {
		printf("%d\n", recvd_vals[i]);
		fprintf(fp, "%d \n", recvd_vals[i]);//writing to file
	}

	fclose(fp);
    free(recvd_vals);


	return 0;
}
