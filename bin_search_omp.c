// Binary Search using Reduction and open mp

#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	int n;
	printf("Enter No of elements in array: ");
	scanf("%d",&n);
	
	int arr[n];
	for (int i=0; i<n; i++)
	{
		arr[i] = i+1;
	}

    
	for (int i=0; i<n; i++)
	{
		printf("%d ",arr[i]);
	}
    printf("\n");

    
	int search_val;
    bool exists = false; 

	printf("Enter No. to be searched: ");
	scanf("%d",&search_val);

    omp_set_num_threads(100);

    int mid=0, first=0, last=n-1;
	
	
    while (first != last)
    {
        mid = (first+last)/2;
        #pragma omp parallel
        {
        
            #pragma omp sections 
            {
                #pragma omp section
                {
                    if (search_val == arr[mid]) {
                        exists = true;
                    }
                    else
                        ompd_bp_thread_end(); 
                }

                #pragma omp section
                {
                    if (search_val > arr[mid]) {
                        first = mid+1;
                    }
                    else
                        ompd_bp_thread_end();
                }

                #pragma omp section
                {
                    if (search_val < arr[mid]) {
                        last = mid-1;
                    }   
                    else
                        ompd_bp_thread_end();
                }
        
            }
        }      
    
    }

    if(!exists)
        printf("Element Not Found\n");
    else 
        printf("Element Has Been Found\n");
}