#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

// Addition of Array elements 

int main()
{
	long size;
	printf("Enter the size of the array : \n");
	scanf("%ld",&size);
	int array[size];

	//generating random array:
	srand(time(0));
	for(int i=0; i<size; i++)
		array[i] = rand() % 100+1;

	printf("\n\n");

	//printfing the array generated;
	for(int i=0; i<size; i++)
		printf("%d ",array[i]);

	omp_set_num_threads(5);
	int sum=0;
	#pragma omp parallel for
	for(int i=0; i<size ; i++)
	{
		printf("Thread id[%d] worked\n",omp_get_thread_num());
		sum+=array[i];
	}

	printf("\n\nThe sum of the elements of the array = %d\n",sum);
	return 0;
}
