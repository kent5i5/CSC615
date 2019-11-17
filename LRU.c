#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define QUEUE_SIZE 3
#define nRefString 20


/*
 * LRU page replacement algorithm implementation:
 * For LRU, the idea is to associate each entry with timer/counter.
 * First, we fill the queue with reference strings, 
 * when the queue is full and a new page reference comes in,
 * we check if the new page reference is already exists and assigned a new counter value to it. 
 * If a match value is not found, we run a search algorithm to find the smallest counter in the queue.
 * When the program find out which element is the least used/updated and the location of it 
 * insert new reference string at that location of the queue.
 * I have a faults variable counting the number of page faults during the procdure.
 */
int main()
{	
	int queue[QUEUE_SIZE];
	int qTime[QUEUE_SIZE];
	int referenceString[1000];
	int counter;
	int i;
	int j;
	int k;
	int faults;
	int nextswap;
	int match;
	int temp;
	int z;
	//initialize all values
	counter = 0;
	i =0;
	j =0;
	k =0;
	faults = 0;
	nextswap =0;
	match =0;
	temp = 0;
	z = 0;
	printf("Running with buffer size %d \n", QUEUE_SIZE);
	printf("Resolving %d reference Strings \n", nRefString);
	/*initialize random seed*/
	srand( time(NULL));
	
	/*generate */
	printf("reference stings: ");
	while (i < nRefString) {
		referenceString[i] = rand()%11 + 1; 
		printf(" %d " , referenceString[i]);
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
					qTime[j] = counter;   // also upgrate the counter for the same item
					counter++;
					//same reference string cause no fault
				}
				j++;	
		}
		j =0;
		//if no match is found , insert the new item
		if (match == 0){
			queue[k] = referenceString[i];
			qTime[k] = counter;	
			counter++;
			k++;
			faults++; 
			
		}
		match =0;
		i++;
					
	}
	k = 0;
	//printf("counters %d %d %d", qTime[0], qTime[1], counter);
	printf("Initial state: beign with %d faults \n", faults); 
	//printf("location \t %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d \n" , 1,2,3,4,5,6,7,8,9,10,11);
	printf("         \t ");
	j = 0;
	while (j < QUEUE_SIZE){
		printf("%d  ",queue[j]);
		j++;
	}
	printf("\n *** \n");
	
	/*then fill the rest by comparing new entry to existing items, 
	  each time Insert an item , check page faults*/
	//i = QUEUE_SIZE;
	//printf("location \t\t\t\t\t%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d \n" , 1,2,3,4,5,6,7,8,9,10,11);
	printf(" ---------- \n ");
	while(k < (nRefString) && referenceString[i] > 0 ){
	j=0;
	printf(" Next Input: %d ", referenceString[i]);
	while(j < QUEUE_SIZE){
		
		if ( queue[j] == referenceString[i]){
			match = 1;
			qTime[j] = counter;
			counter++;
			printf("upgrate the counter of location %d , item-%d ->\t",j+1, queue[j]);
			break;
		}
		j++;

		
	}
	
	/*if no match*/
	if (match == 0){
		
		//search for the least used item
		j = 0;
		temp = qTime[j];
		z = 0;
		nextswap = 0;		
		while (j < QUEUE_SIZE){
			
			
			if ( temp > qTime[j] ){
				temp = qTime[j];
				z = j;
			}else if( temp < qTime[j]) {
				//temp = qTime[j];
				 
			}else;			
			j++;
		}
		
		nextswap = z;	
		printf("swap %dth item-%d ", z+1, queue[nextswap]);
		//printf("z %d ,nextswap %d \n",z ,nextswap);
		queue[nextswap] = referenceString[i];
		printf(" with %d -> \t\t\t",queue[nextswap]);		
		qTime[nextswap] = counter; 
		counter++;
		temp = 0;
		/*if (nextswap != (QUEUE_SIZE-1))
			nextswap += 1;
		else 
			nextswap = 0;	*/		

		faults++;
	}
		j = 0;
		while (j < QUEUE_SIZE){
			printf("%d  ",queue[j]);
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
}  //End of LRU algorithm






