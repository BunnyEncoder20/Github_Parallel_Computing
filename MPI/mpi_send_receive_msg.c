/* test of MPI */ 
#include "mpi.h" 
#include <stdio.h> 
#include <string.h> 

int main(int argc, char **argv) 
{ 
   char reply[100]; 
   char buff[128]; 
   int numprocs; 
   int myid; 
   int i; 
   MPI_Status stat; 

   MPI_Init(&argc,&argv); 
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
   MPI_Comm_rank(MPI_COMM_WORLD,&myid); 

   if(myid == 0) 
   { 
      printf("WE have %d processors\n", numprocs); 

      for(i=1;i<numprocs;i++) 
      { 
	 sprintf(buff, "Hello %d", i); 
	 MPI_Send(buff, 128, MPI_CHAR, i, 0, MPI_COMM_WORLD); 
      } 

      for(i=1;i<numprocs;i++) 
      { 
         MPI_Recv(buff, 128, MPI_CHAR, i, 0, MPI_COMM_WORLD, &stat); 
         printf("%s\n", buff); 
      } 
   } 
   else 
   { 
      MPI_Recv(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &stat); 

      sprintf(reply, " |--> Hello 0, Processor %d is present and accounted for !",myid); 
      strcat(buff, reply);
      MPI_Send(buff, 128, MPI_CHAR, 0, 0, MPI_COMM_WORLD); 
   } 

   MPI_Finalize(); 
}


