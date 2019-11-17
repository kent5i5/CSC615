#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define QUEUE_SIZE 3
#define nRefString 20


/*
 * OPT/MIN page replacement algorithm implementation:
 * Here I have the entrie referenece string presented.
 * First, we fill the queue with reference strings and count the faults.
 * when the queue is filed and a new page reference comes in,
 * we check if the new page reference is already exists and use the OPT. 
 * For OPT, I run a search algorithm to find the most unlikely page reference 
 * in the rest of ref. string. Then insert that ref. String at that location of the queue.
 * The way I did is counting the occurence of the each element in the queue(a array),
 * and have another array storing the result coresponding to the element in the same location.
 * I have a faults variable counting the number of page faults during the procdure.
 */
int main()
{	
	int queue[QUEUE_SIZE];
	int qbuffer[QUEUE_SIZE];
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
	int q;
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
	q =0;
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
	while (k < QUEUE_SIZE && i < nRefString){
		j =0;
		// check if the item already exists
		
		while(j < QUEUE_SIZE && match != 1){
				if (queue[j] == referenceString[i]){
					match =1;
					///qTime[j] = counter;   // also upgrate the counter for the same item
					///counter++;
					//same reference string cause no fault
				}
				j++;	
		}
		j =0;
		//if no match is found , insert the new item
		if (match == 0){
			queue[k] = referenceString[i];
			///qTime[k] = counter;	
			///counter++;
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
	while (j < QUEUE_SIZE && referenceString[j] > 0){
		printf("%d  ",queue[j]);
		j++;
	}
	printf("\n *** \n");
	//////---------------------------------------------------------------------below is the search algorithm

	/* count the occurences of the each in the rest of reference strings, then I store the counter in the corresponding location of each page reference.
	  then compare each of all elements in the queue , I take the one with less count.
	  If two victim page ref. has the count, I get the fronter and replace it*/
	//i = QUEUE_SIZE;
	//printf("location \t\t\t\t\t%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d \n" , 1,2,3,4,5,6,7,8,9,10,11);
	
	printf(" ---------- \n ");
	while(k < (nRefString) && referenceString[i] > 0 ){ //the out most loop
	counter= 0;
	j = 0;
	//printf(" i: %d ", i);
	//printf(" Next Input: %d ", referenceString[i]);
	/*Get the count for each page ref. in the queue*/
	while(j < QUEUE_SIZE ){
		q=i;
		while( q < nRefString){
			
				/*count from the rest of ref. strings*/
				if(queue[j] == referenceString[q])  
					counter++;			
			q++;
			//break;
		}
		qbuffer[j] = counter;
		counter =0;
		j++;
	
		
	}  //end of aquiring counts
	j=0;
	while (j < QUEUE_SIZE){
		printf("pairs %d-%d ->\t",j+1, qbuffer[j]);
		j++;
	}
	printf("\t");
	j=0;
	//printf(" Next Input: %d ", referenceString[i]);
	while(j < QUEUE_SIZE){
		
		if ( queue[j] == referenceString[i]){
			match = 1;
			//printf("upgrate the counter of location %d , item-%d ->\t",j+1, queue[j]);
			break;
		}
		j++;	
	} // check if the element is already in queue

	if (match == 0){
		
		//search for the least used item in the future
		j = 0;
		temp = qbuffer[j];
		z = 0;
		nextswap = 0;		
		while (j < QUEUE_SIZE){
					
			if ( temp > qbuffer[j] ){ //if temp == qbuffer[j], I keep temp and z
				temp = qbuffer[j];
				z = j;
			}

			j++;			
		}
		//nextswap gets the result
		nextswap = z;	
		printf("swap %dth item-%d ", z+1, queue[nextswap]);
		queue[nextswap] = referenceString[i];
		printf(" with %d -> \t",queue[nextswap]);		
		temp = 0;
		
		faults++;
	}
		j = 0;
		while (j < QUEUE_SIZE && referenceString[i] > 0){
			printf("%d  ",queue[j]);
			j++;
		}
	printf(" with %d faults |***| \n", faults);
	j = 0;
	match = 0;
	k++;
	i++;
	} //end of outer most while loop
	printf("\n");
	printf("Number of page faults = %d \n", faults);	
	return 0;
}  //End of LRU algorithm






