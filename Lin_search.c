//Linear search using Reduction
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main(){
	int i,sum=0,len=10,key=0,v[len];

	printf("Enter the key value :  \n");
	scanf("%d",&key);
	omp_set_num_threads(6);

	srand(time(0));
	printf("\n");
	#pragma omp parallel shared(v,len,key) private(i)
	{
		#pragma omp for		//initializing the vector
		for(i=0;i<len;i++)
			v[i] = rand() % 10+1;

		#pragma omp for
		for(i=0;i<len;i++)
			printf(" - %d ",v[i]);

		#pragma omp for reduction(+:sum)
		for(i=0;i<len;i++){
			if(v[i]==key)
				sum+=v[i];
		}
	}

	if(sum>0)
	{
		printf("\nThe key value exists in the vector\n");
		printf("It occures %d times\n",sum/key);
	}
	return 0;
}
