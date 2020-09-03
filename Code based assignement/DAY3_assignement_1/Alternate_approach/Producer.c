#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
#include "common.h"
int main(int argc, char **argv)
{
	//declaring mq, attributes, and opening file in w mode

	mqd_t mq;
	struct mq_attr attr;
	char buffer[MAX_SIZE + 1] = {'\0'};
	int *gend_vals;
	srand(time(NULL));

	/* initialize the queue attributes */

	FILE* fp;
	fp = fopen("producer.txt", "w");
	if (fp == NULL)
		exit(-1);
	int max_vals = 1000;
	int val_count = 0;


	attr.mq_flags = 0;//Blocking send
	attr.mq_maxmsg = 10;//MQ Size
	attr.mq_msgsize = MAX_SIZE;
	attr.mq_curmsgs = 0;

	/* create the message queue */
	mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
	CHECK((mqd_t) - 1 != mq);

	/* allocating array for produced vals */
	gend_vals = malloc (max_vals * sizeof(int));
	if (gend_vals == NULL) {
		printf("gend_vals malloc error\n");
		exit(1);
	}

	while (val_count < max_vals)
	{

		mq_getattr(mq, &attr);

		if (attr.mq_curmsgs < attr.mq_maxmsg)
		{
			int random = rand() % 10;
			gend_vals[val_count++] = random;
			sprintf(buffer, "%d", random);          //converting int to string for writing to file
			CHECK(0 <= mq_send(mq, buffer, MAX_SIZE, 0));//sending msg to q
			attr.mq_curmsgs++;
		}
	}

	printf("Producer produced:\n");
	for (int i = 0; i < max_vals; i++) {
		printf("%d\n", gend_vals[i]);
		fprintf(fp, "%d \n", gend_vals[i]);
	}
	fclose(fp);
	/* cleanup */
    free(gend_vals);
	CHECK((mqd_t) - 1 != mq_close(mq));
	CHECK((mqd_t) - 1 != mq_unlink(QUEUE_NAME));

	return 0;
}
