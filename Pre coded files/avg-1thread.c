#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

#define RAND() (drand48()) /* basic Linux random number generator */

//Structure for arguments passed to thread

struct arg_struct
{
	int size;
	double *data;
};

//Structure to store results passed back from threads

struct result_struct
{
	double sum;
};

void *SumThread(void *arg)
{
	int i;
	double my_sum;
	struct arg_struct *my_args;
	int my_size;
	double *my_data;
	struct result_struct *result;

	printf("sum thread running\n");

	my_args = (struct arg_struct *)arg;
	my_size = my_args->size;
	my_data = my_args->data;

	result = (struct result_struct *)malloc(sizeof(struct result_struct));
	if(result == NULL) {
		exit(1);
	}

	free(my_args);

	my_sum = 0.0;
	for(i=0; i < my_size; i++) {
		my_sum += my_data[i];
	}

	result->sum = my_sum;
	printf("sum thread done, returning\n");

	return((void *)result);
}

int main(int argc, char **argv)
{
	int i;
	int n;
	double *data;
	int count;
	struct arg_struct *args;
	pthread_t thread_id;
	struct result_struct *result;
	int err;

	if(argc <= 1) {
		fprintf(stderr,"Must specify count\n");
		exit(1);
	}

	count = atoi(argv[1]);	/* count is first argument */ 

	if(count <= 0) {
		fprintf(stderr,"invalid count %d\n",count);
		exit(1);
	}
	
	data = (double *)malloc(count * sizeof(double));
	if(data == NULL) {
		exit(1);
	}

	// Create random numbers

	for(i=0; i < count; i++) {
		data[i] = RAND();
	}

	args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
	if(args == NULL) {
		exit(1);
	}

	args->size = count;
	args->data = data;

	// fork off a thread to get the sum from the data

	printf("Main thread forking sum thread\n");
	fflush(stdout);
	err = pthread_create(&thread_id, NULL, SumThread, (void *)args);
	if(err != 0) {
		fprintf(stderr,"pthread create failed\n");
		exit(1);
	}

	printf("main thread running after sum thread created, about to call join\n");

	// wait until the sum thread is finished and get the result back

	err = pthread_join(thread_id,(void **)&result);
	if(err != 0) {
		fprintf(stderr,"pthread_join failed\n");
		exit(1);
	}
	printf("main thread joined with sum thread\n");

	printf("The average over %d random numbers on (0,1) is %f\n",
			count, result->sum / (double)count);

	free(result);

	free(data);

	return(0);
}
