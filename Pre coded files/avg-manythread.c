#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

#define RAND() (drand48()) /* basic Linux random number generator */

struct arg_struct
{
	int id;
	int size;
	double *data;
	int starting_i;
};

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
	int my_start;
	int my_end;
	int my_id;

	my_args = (struct arg_struct *)arg;
	result = (struct result_struct *)malloc(sizeof(struct result_struct));
	if(result == NULL) {
		exit(1);
	}

	printf("sum thread %d running, starting at %d for %d\n",
		my_args->id,
		my_args->starting_i,
		my_args->size);


	my_id = my_args->id;
	my_size = my_args->size;
	my_data = my_args->data;
	my_start = my_args->starting_i;

	free(my_args);

	my_end = my_start + my_size;

	my_sum = 0.0;
	for(i=my_start; i < my_end; i++) {
		my_sum += my_data[i];
	}

	result->sum = my_sum;

	printf("sum thread %d returning\n",	my_id);


	return((void *)result);
}

int main(int argc, char **argv)
{
	int i;
	int t;
	double sum;
	double *data;
	int count;
	int threads;
	struct arg_struct *args;
	struct result_struct *result;
	int err;
	pthread_t *thread_ids;
	int range_size;
	int index;

	count = atoi(argv[1]);	/* count is first argument */ 

	if(count <= 0) {
		fprintf(stderr,"invalid count %d\n",count);
		exit(1);
	}

	threads = atoi(argv[2]); /* thread count is second arg */

	if(threads <= 0) {
		fprintf(stderr,"invalid thread count %d\n",threads);
		exit(1);
	}


	 //don't allow more threads than data elements

	if(threads > count) {
		threads = count;
	}

	 // make an array large enough to hold #count# doubles

	data = (double *)malloc(count * sizeof(double));
	if(data == NULL) {
		exit(1);
	}

	for(i=0; i < count; i++) {
		data[i] = RAND();
	}


	/*
	 * make a data structure to hold the thread ids so that the spawning
	 * thread can join with each one separately
	 */
	thread_ids = (pthread_t *)malloc(sizeof(pthread_t)*threads);
	if(thread_ids == NULL) {
		exit(1);
	}

	range_size = (count / threads) + 1;

	// handle the possibility that #threads# divides #count# evenly

	if(((range_size-1) * threads) == count) {
		range_size -= 1;
	}

	printf("main thread about to create %d sum threads\n",threads);

	index = 0;
	for(t=0; t < threads; t++) {
		args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
		if(args == NULL) {
			exit(1);
		}
		
		args->id = (t+1);
		args->size = range_size;
		args->data = data;
		
		args->starting_i = index;
		
		if((args->starting_i + args->size) > count) {
			args->size = count - args->starting_i;
		}
		printf("main thread creating sum thread %d\n",t+1);

		err = pthread_create(&(thread_ids[t]), NULL, SumThread, (void *)args);
		if(err != 0) {
			fprintf(stderr,
				"pthread create failed for thread %d\n", t);
			exit(1);
		}
		printf("main thread has created sum thread %d\n",t+1);
		
		index += range_size;
	}

	/*
	 * join with each thread one at a time and
	 * get its partial sum and make a global sum
	 */
	sum = 0;
	for(t=0; t < threads; t++) {
		// wait until the next sum thread is finished and get the result back

		printf("main thread about to join with sum thread %d\n",t+1);
		err = pthread_join(thread_ids[t],(void **)&result);
		if(err != 0) {
			fprintf(stderr,"pthread_join failed for thread %d\n",t);
			exit(1);
		}
		printf("main thread joined with sum thread %d\n",t+1);
		
		// add in the partial sum
		sum += result->sum;
		
		free(result);
	}

	printf("The average over %d random numbers on (0,1) is %f\n", count, sum / (double)count);

	free(thread_ids);
	
	free(data);

	return(0);
}


