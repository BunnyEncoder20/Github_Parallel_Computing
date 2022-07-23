#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

//Lab 1 - Work Sharing

void *IDfunc(void *tid)
{
	long *myID = (long *) tid;
	printf("Hello! This is thread with ID %ld\n",*myID);
}

int main()
{
	pthread_t tid0;
	pthread_t tid1;
	pthread_t tid2;
	pthread_t *threads[] = {&tid0,&tid1,&tid2};
	
	for(int i=0;i<3;i++)
	{
		pthread_create(threads[i],NULL,IDfunc,(void*)&threads[i]);
		pthread_join(*threads[i], NULL);
	}
	
	//pthread_exit(NULL);
	
	
	return 0;
}
