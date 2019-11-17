#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define QUEUE_SIZE 3
#define nRefString 20

/*
 * FIFO implementation:
 * I make the array behave like first in first out queue to hold all pages in memory. 
 * First, filling the array with page references, when the page is brought into memory
 * when the queue is full and a new page reference comes in, I check if it is already in the queue.
 * If new one does not exsit, I replace the old page reference that is the first item in the array
 * with the new page reference. I have the nextswap work as a director, it points the next oldset page
 * reference. For each replacement action, I increment the nextswap by 1. If it reaches maximum queue
 * size, I reset it to 0 redirecting to the first item in the array. 
 * I have a faults variable counting the number of page faults.
 */
int main()
{	
	int queue[QUEUE_SIZE];
	int referenceString[1000];
	int i;
	int j;
	int k;
	int faults;
	int nextswap;
	int match;
	printf("Running with buffer size %d \n", QUEUE_SIZE);
	printf("Resolving %d reference Strings \n", nRefString);
	/*initialize all the values*/
	i =0;
	j =0;
	k =0;
	faults = 0;
	nextswap =0;
	match =0;
	/*initialize random seed*/
	srand( time(NULL));
	
	/*generate */
	printf("reference stings: \n");
	while (i < nRefString) {
		referenceString[i] = rand()%11 + 1; 
		printf("%d " , referenceString[i]);
		
		i++;
	}
	printf("Finish the generation \n" );
	/*first fill the queue with generated numbers*/
	i =0;
	while (k < QUEUE_SIZE && referenceString[i] > 0){
		j =0;
		// check if the item already exists
		
		while(j < QUEUE_SIZE && match != 1){
				if (queue[j] == referenceString[i]){
					match =1;
					//same reference string cause no fault
				}
				j++;	
		}
		j =0;
		//if no match is found , insert the new item
		if (match == 0){
			queue[k] = referenceString[i];	
			k++;
			faults++; 
			
		}
		match =0;
		i++;
					
	}
	k =0;
	printf("Initial state: being with %d faults \n", faults);  
	//printf("location \t %d %d %d %d %d %d %d %d %d %d %d \n" , 1,2,3,4,5,6,7,8,9,10,11);
	printf("         \t ");
	j = 0;
	while (j < QUEUE_SIZE){
		printf("%d ",queue[j]);
		j++;
	}
	printf("\n *** \n");
	
	/*then fill the rest by comparing new entry to existing items, 
	  each time Insert an item , check page faults*/
	//i = QUEUE_SIZE;
	while(k < (nRefString) && referenceString[i] > 0 ){
	j=0;
	while(j < QUEUE_SIZE){
		
		if ( queue[j] == referenceString[i]){
			match = 1;
			printf(" %d is in the queue ", queue[j]);
		}
		j++;
		
	}
	/*if no match*/
	if (match == 0){
		printf("swap out %d ", queue[nextswap]);
		queue[nextswap] = referenceString[i];
		printf("swap in %d | ", queue[nextswap]);
		if (nextswap != (QUEUE_SIZE-1))
			nextswap += 1;
		else 
			nextswap = 0;			

		faults++;
	}
		j = 0;
		while (j < QUEUE_SIZE){
			printf("%d ",queue[j]);
			j++;
		}
	printf(" with %d faults |***| \n", faults);
	j = 0;
	match = 0;
	k++;
	i++;
	}
	printf("\n");
	printf("Number of page faults = %d \n", faults);	
	return 0;
}  //End of FIFO algorithm 






