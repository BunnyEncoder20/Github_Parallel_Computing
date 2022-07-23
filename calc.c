#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int main()
{
	int total=0;
	for(int i=1;i<21;i++){total+=i;}
	printf("Total = %d\n",total);
	return 0;
}

