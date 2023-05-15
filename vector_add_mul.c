#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

// Code for vector addition and Multiplication

int main()
{
	int size;
	scanf("%d",&size);

	//vectorC for addition, vectorD for multiplication
	int vectorA[size],vectorB[size],vectorC[size],vectorD[size];

	//generating random values for vectorA and vectorB
	srand(time(0));
	for(int i=0; i<size; i++)
	{
		vectorA[i] = rand() % 100+1;
		vectorB[i] = rand() % 100+1;
	}


	printf("\nVectorA : ");

	for(int i=0; i<size; i++)
	{
		printf("%d ",vectorA[i]);
	}

	printf("\nVectorB : ");

	for(int i=0;i<size;i++)
	{
		printf("%d ",vectorB[i]);
	}

	printf("\n\n");

	omp_set_num_threads(5);
	#pragma omp parallel
	{
		printf("Number of threads : %d\n",omp_get_num_threads());
		int tid = omp_get_thread_num();
		printf("Thread id[%d] starting\n",tid);
		
		#pragma omp sections nowait
		{
			#pragma omp section
			{
				printf("Thread [%d] doing section1\n",omp_get_thread_num());
				for(int i=0;i<size;i++)
				printf("Thread [%d]: C[%d] = %d\n",omp_get_thread_num(),i,vectorA[i]+vectorB[i]);

			}

			#pragma omp section
			{
				printf("Thread [%d] doing section2\n",omp_get_thread_num());
				for(int i=0;i<size;i++)
				printf("Thread [%d]: D[%d] = %d\n",omp_get_thread_num(),i,vectorA[i]*vectorB[i]);

			}
		}
		printf("Thread id[%d] completed.\n",tid);
	}


	return 0;
}

