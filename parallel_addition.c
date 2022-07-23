#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// problem : find sum of the array elements but by using multiple threads

int array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; 

void *routine(void *args){
	int index = *(int*)args; free(args);
	int sum=0;
	for(int i=index;i<index+5;i++)
	{sum+=array[i];}
	int *result = malloc(sizeof(int)); *result=sum;
	return (void*)result;
}

int main()
{
	pthread_t threads[4];
	int initial=0;
	for(int i=0;i<4;i++){
		int *index = malloc(sizeof(int)); *index=initial;
		if (pthread_create(&threads[i],NULL,&routine,index)!=0){perror("error_404\n");}
		initial+=5;
	}
	
	int total=0;
	for(int i=0;i<4;i++)
	{
		int *result;
		if (pthread_join(threads[i],(void**)&result)!=0){perror("error_404\n");}
		total+=*result; 
		printf("sub_sum = %d\n",*result);
		free(result);
	}

	printf("The Total of the array is = %d\n",total);
	return 0;
}
