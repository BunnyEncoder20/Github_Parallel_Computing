#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

struct thread_data
{
	int a ;	//int a=43  : We cannot assign value directly in a structure;
	int b ;	//int b=26 : Cause Structure just define a structure of data types and do not have space allocated in memory
	//space is allocated only when we create a object of that structure 
};

void* func(void* args)
{
	struct thread_data my_data = *(struct thread_data*)(args); //dereferencing the structure obj
	int a = my_data.a;
	int b = my_data.b;
	printf("Sum = %d\n ...Nice...\n",a+b);
}

int main()
{
	pthread_t thread;
	struct thread_data obj;
	obj.a=26; obj.b=43; 
	
	if(pthread_create(&thread,NULL,&func,&obj)!=0)
	{perror("There seems to be an error\n");}
	
	if(pthread_join(thread,NULL)!=0)
	{perror("There seems to be an error\n");}
	
	return 0;
}
