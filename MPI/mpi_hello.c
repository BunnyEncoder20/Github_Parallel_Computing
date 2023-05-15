#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define  MASTER		0

int main (int argc, char *argv[])
{
	int   numtasks, taskid, len;
	
	char hostname[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Init(&argc, &argv);
		
	// Get the number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	
	// Get the rank of the process
	MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
	
	// Get the name of the processor
	MPI_Get_processor_name(hostname, &len);
	
	printf ("Hello from task %d on %s!\n", taskid, hostname);
	
	if (taskid == MASTER)
	   printf("MASTER: Number of MPI tasks is: %d\n",numtasks);
	   
	MPI_Finalize();

}
