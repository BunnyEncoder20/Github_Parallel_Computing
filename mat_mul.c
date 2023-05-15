#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

//write parallel executing code for matrix multiplication

//generating random matric using malloc

#define maxi 10;

#define mini 1;

/*
int** srand_square_matrix(int dimensions){
	int** matrix  = malloc(dimensions*sizeof(int*));

	for(int i=0; i<dimensions; i++)
		matrix[i] = malloc(dimensions*sizeof(int));

	//making 2D array of pointers completed

	//generating a random seed each time
	srand(time(0));

	//genrerating the matrix
	//notice how the parallel for block of pragma is structured :-
	#pragma omp parallel for
	for(int i=0; i<dimensions; i++)
	{
		for(int j=0; j<dimensions; j++)
		{
			matrix[i][j] = rand() % maxi + mini;
		}
	}

	return matrix;
}


int sequential_multiplication(int** matA, int** matB, int dimension)
{
	int** matC = malloc(dimension*sizeof(int*));

	for(int i=0; i<dimension; i++)
	{
		for(int j=0; j<dimension; j++)
		{
			for(int k=0;k<dimension; k++)
			{
				matC[i][j] += matA[i][k]*matB[k][j];
			}
		}
	}

	printf("\n\nMatrix C : \n");
	for(int i=0; i<dimension; i++)
	{
		for(int j=0; j<dimension; j++)
		{
			printf("%d ",matC[i][j]);
		}
		printf("\n");
	}
}

int parallel_multiplication(int** matA, int** matB, int dimension)
{
	int** matC = malloc(dimension*sizeof(int*));

	#pragma omp parallel for
	for(int i=0; i<dimension; i++)
	{
		for(int j=0; j<dimension; j++)
		{
			for(int k=0; k<dimension; k++)
			{
				matC[i][j] += matA[i][k]*matB[k][j];
			}
		}
	}

	printf("\n\nThe Kooler Matrix C : \n");
	for(int i=0; i<dimension; i++)
	{
		for(int j=0; j<dimension; j++)
		{
			printf("%d ",matC[i][j]);
		}
		printf("\n");
	}
}
*/


int main()
{
	int size;
	printf("Enter the dimensions of the square matrix : \n");
	scanf("%d",&size);

	omp_set_num_threads(6);

	int matA[size][size];
	int matB[size][size];
	
	srand(time(0));


	#pragma omp parllel for
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			matA[i][j] = rand() % maxi + mini;
			matB[i][j] = rand() % maxi+mini;
		}
	}

	printf("\n\nMatix A\n");
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			printf("%d ",matA[i][j]);
		}
		printf("\n");
	}

	printf("\n\nMatrix B\n");
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			printf("%d ",matB[i][j]);
		}
		printf("\n");
	}

	int matC[size][size];
	for(int i=0; i<size;i++)
	{
		for(int j=0;j<size;j++)
		{matC[i][j] = 0;}
	}
	
	#pragma omp parallel for
	for(int i=0; i<size; i++)
		{
			printf("Thread id[%d] working",omp_get_num_threads());
			for(int j=0; j<size; j++)
			{
				for(int k=0; k<size; k++)
				{
					matC[i][j] += matA[i][k]*matB[k][j];
				}
			}
		}

	printf("\n\nThe Kooler Matrix C : \n");
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			printf("%d ",matC[i][j]);
		}
		printf("\n");
	}
//	sequential_multiplication(matA, matB, dimensions);
//	parallel_multiplication(matA, matB, dimensions);


	return 0;
}
