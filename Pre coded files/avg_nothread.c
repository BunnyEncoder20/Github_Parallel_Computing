#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define RAND() (drand48()) /* basic Linux random number generator */

int main(int argc, char **argv)
{
	int i;
	int n;
	double *data;
	double sum;
	int count;

	if(argc <= 1) {
		fprintf(stderr,"must specify count\n");
		exit(1);
	}

	count = atoi(argv[1]);	/* count is first argument */ 

	if(count <= 0) {
		fprintf(stderr,"invalid count %d\n",count);
		exit(1);
	}

	data = (double *)malloc(count * sizeof(double));
	if(data == NULL) {
		exit(1);
	}

	// Generate random numbers
	for(i=0; i < count; i++) {
		data[i] = RAND();
	}

	// compute the sum

	sum = 0;
	for(i=0; i < count; i++) {
		sum += data[i];
	}

	printf("The average over %d random numbers on (0,1) is %f\n",
			count, sum/(double)count);

	free(data);

	return(0);
}
