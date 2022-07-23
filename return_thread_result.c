#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

void *routine() //roll a dice
{
	int result = (rand()%6)+1;	// rand()%6 will generate random numbers from 0-5. Hence the +1 in the end.
	//printf("Dice : %d\n",result);
	
	// return (void*)&result;	
	// need to return a pointer to a pointer . Return type of function is void pointer hence the typecasting 
	// typecasting + &-reference = void** or pointer to pointer ?  WRONG !
	// you are returning a refernce of a local variable ! The local variable will be deallocated once thread completes
	// NEED to dynamically allocate the memory so that it doesn't occur
	// also do not forgte to type cast the pointer apropriately ! it must be a [void pointer to pointer]
	int *return_value = malloc(sizeof(int)); 
	*return_value = result;
	return (void*)return_value;
}

int main()
{
	srand(time(NULL));
	int *result;
	pthread_t threads[3];
	for(int i=0;i<3;i++)
	{
		if (pthread_create(&threads[i],NULL,&routine,NULL)!=0){perror("There has been an error\n");}
	}
	for(int i=0;i<3;i++)
	{
		if (pthread_join(threads[i],(void**)&result)!=0){perror("There has been an error\n");}
		// don't forget to type cast the return void** 
		printf("Dice : %d\n",*result); 
		free(result); //remember to free the dynamically allocated memory
	}
	return 0;
}
