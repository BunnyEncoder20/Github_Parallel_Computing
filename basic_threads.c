#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int array1[]={1,2,3,4,5,6,7,8,9,10};

int array2[]={1,2,3,4,5,6,7,8,9,10};

void *func(void* args)
{
	int index = *(int*)args;
	printf("%d ",array1[index]);
	free(args);
}

int main()
{
	pthread_t thread_arr[10];
	
	printf("The numbers are :\n");
	for(int i=0; i<10 ; i++)
	{
		int* a = malloc(sizeof(int)); *a=i;
		if(pthread_create(&thread_arr[i],NULL,&func,a)!=0)
		{ perror("There has been an ERROR !"); }
	}
	
	for(int i=0; i<10 ; i++)
	{
		if(pthread_join(thread_arr[i],NULL)!=0)
		{ perror("There has been an ERROR !"); }
	}
	return 0;
}
