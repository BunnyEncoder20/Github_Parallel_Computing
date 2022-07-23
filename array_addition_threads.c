#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int a1[] = {1,2,3,4,5}; int a2[] = {6,7,8,9,10};
int b1[] = {1,2,3,4,5}; int b2[] = {6,7,8,9,10};

/*
void *routine() //roll a dice
{
	int result = (rand()%6)+1;	
	int *return_value = malloc(sizeof(int)); 
	*return_value = result;
	return (void*)return_value;
} */

void* routine1(void* args)
{
	int index = *(int*)args;
	printf("a1[%d] + b1[%d] = %d\n",index,index,a1[index]+b1[index]);
	free(args);
}

void* routine2(void* args)
{
	int index = *(int*)args;
	printf("a2[%d] + b2[%d] = %d\n",index,index,a2[index]+b2[index]);	
	free(args);
}

int main()
{
	pthread_t thread1[5]; 
	pthread_t thread2[5];
	
	for(int i=0;i<5;i++){
		int *index1 = malloc(sizeof(int)); *index1 = i;
		int *index2 = malloc(sizeof(int)); *index2 = i;
		if(pthread_create(&thread1[i],NULL,&routine1,index1)!=0) {perror("ERROR");}
		if(pthread_create(&thread2[i],NULL,&routine2,index2)!=0) {perror("ERROR");}
	}
	
	for(int i=0;i<5;i++){
		if(pthread_join(thread1[i],NULL)!=0) {perror("ERROR");}
		if(pthread_join(thread2[i],NULL)!=0) {perror("ERROR");}
	}
	

	return 0;
}
