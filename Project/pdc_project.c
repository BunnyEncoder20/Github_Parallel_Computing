//*******************************************************************
//	Password Matching for a large password file using MPI
//*******************************************************************

//***************************
//		Libraries :
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>	
#include<ctype.h>
#include<string.h>
#include<time.h>
//***************************


// Function FindPassword finds the password (pass) from the input MPI file and also requires the MPI Comm size , MPI Comm rank
// character overlay (olap)

int FindPassword(MPI_File *input, char *pass, int length, const int rank, const int size, const int olap)
{
    //Init the needed variables 
	MPI_Offset starting_offset;
	int mysize; char *buff;
	
	MPI_Offset ending_offset;
	MPI_Offset file_size;
	
	//fetching  the file size 
	MPI_File_get_size(*input,&file_size);
	
	//removing the eof
	file_size--;
	
	//file size to be handled by each process :
	mysize = file_size/size;
	
	//assigning the starting offset to the process :
	starting_offset = rank * mysize
	
	//assigning the ending_offset to the process:
	ending_offset = starting_offset + mysize - 1;
	
    //For last process assign ending_offset accordingly
    if(rank == size-1)
        ending_offset = file_size-1;
    
	//Add overlap to the end of everyone's buff except the last process
	if(rank != size-1)
		ending_offset += olap;
	
	mysize = ending_offset - starting_offset + 1;
	
	//Allocate memory
	buff = malloc((mysize+1)*sizeof(char));
	
	//Every process reads it's parts :
	MPI_File_read_at_all(*input, starting_offset, buff, mysize, MPI_CHAR, MPI_STATUS_IGNORE);
	
	//Assigning the eof character to the extra last place
	buff[mysize] = '\0';
	
	//Set up the readin position rank wise
	int locstart = 0 , locend=mysize-1;
	
	if(rank != 0){
		while(buff[locstart] != '\n') locstart++;
		locstart++;
	}
	
	if(rank != size-1){
        locend-=olap;
        while (buff[locend] != '\n') locend++;
    }
    
    //Searching 
    int i = 0, j = 0;
    for(i=locstart; (i<=locend); i++){
        char c = buff[i];
        if(isspace(c)){
            j=0;
            continue;
        }

        if((j<length) && (c == pass[j])){
            j++;
        }

        if(j == length){
            printf("Password Found!\n");
            return 1;
        }
    }

    return 0;
}

//*******************************************************************
//                          Main 
//*******************************************************************

int main(int argc, char **argv){

    //Declare the MPI File variable
    MPI_File input;

    //Declare the rank(id of process) and  size (total processes)
    int rank,size;

    //DEcalre the error cose
    int error_code;

    //ANd the Characte overlap
    const int olap = 100;

    //Init MPI and fecth the input args
    MPI_Init(&argc, &argv);

        //Init the rank according to arguments
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
        //Init the size according to arguements
        MPI_Comm_size(MPI_COMM_WORLD, &size);
    
        //Open the file via MPI and deal with any errors
        error_code = MPI_File_open(MPI_COMM_WORLD, "passwords.txt", MPI_MODE_RONLY, MPI_INFO_NULL, &input);
        if (error_code){
            if(rank == 0)
                fprintf(stderr, "%s: Can't Open the Password File: %s\n", argv[0], argv[1]);
            MPI_Finalize();
            exit(2);
        }
    
        //Setting a Hardcore password to search for
        char * pass = "dobies"; int length = 6;
    
        //Start recording time
        clock_t t = clock();
    
        //Find the password 
        int success = FindPassword(&input, pass, length, rank, size, olap);
        
        //If successful then print the time taken
        if(success == 1){
            printf("Time Taken : %f\n", (float)t/CLOCKS_PER_SEC);
        }
    
        //Close the MPI file
        MPI_File_close(&input);
    
        //Terminate all the processes 
    MPI_Finalize();

    return 0;
}