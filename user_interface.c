#include <stdio.h>	   // It is needed for supporting the input/output  
#include <sys/time.h> // It is needed for accessing the time variables
#include <signal.h>   // It is needed for the signal handling methods
#include <stdlib.h>  // It is needed for compile in new linux version 
#include <fcntl.h>  // It is needed
#include <time.h>      // time.h is required for the ctime() functioon

#define SIZE 256

int i;
int	done;

main(){
	char	mybuf[256];
	char	outbuf[256];	//output buffer
	int	fd;
	int	errs;
	int	count;
	int	n;
	void 	timeout();
	void	realtime();
	struct	itimerval	myvalue,myovalue;
	struct	tm *str_time;	//used to contain the localtime of new time
	struct  itimerval myvalue, myovalue;	//used to set up the setitimer
	struct  timeval my_time;	
	time_t	new_time;	//set up the new time with value from the proc file

	printf("Clearing timer\n");
	timerclear(&myvalue.it_interval);
	timerclear(&myvalue.it_value);
	timerclear(&myovalue.it_interval);
	timerclear(&myovalue.it_value);
	if (( n = setitimer(ITIMER_REAL,&myvalue,&myovalue)) < 0 ) {
		printf("Error in clearing timer\n");
		exit(0);
	}
	i = 0;
	n = 0;
	printf("The beginning time\n");
	realtime(i);
	for ( ;i < 300; ){
	
		printf("Setting up for signals\n");
		printf("Setting signal handler\n");
		if ((signal(SIGALRM, timeout)) == SIG_ERR) {
			printf("Error in setting signal handler\n");
			exit(0);
		}
	
		if ((fd = open ("/proc/myclock",O_RDONLY))< 0){
			perror("Bad open");
			exit(-1);
		}
		while ((count = read(fd, &mybuf[0], sizeof(mybuf))) > 0) {
			//put the two value into two long variable
			sscanf(&mybuf[0],"%d %d",&my_time.tv_sec, &my_time.tv_usec);
			
			//create a new time and convert it to localtime
			new_time = time(&my_time.tv_sec);
			str_time = localtime(&new_time);
			printf("%dst time is: ", i);
			//reformat the local time and write it into a buffer
			strftime(outbuf, SIZE, "%A %d, %I:%M", str_time);
			fputs(outbuf, stdout);
			printf(":%ld",my_time.tv_usec/1000);
		}
		if(count < 0) {
			perror ("Bad read");
			exit (-1);
		}

		printf("Setting timer\n");
		myvalue.it_value.tv_sec = 1; /* timeout interval in seconds */
			/* set tv_usec for microsecond timeout */
		if (( n = setitimer(ITIMER_REAL,&myvalue,&myovalue)) < 0 ) {
			printf("Error in setting timer\n");
			exit(0);
		}
		done = 0;
		printf("Waiting for another signal\n");
		while (!done);
	}
	
	printf("The end time\n");
	realtime(i);

}
	
	

	


/*
 * Display the current time using gettimeofday();
 * 
 */
void
realtime(int arg){
	struct	timeval	mytime2;

	gettimeofday(&mytime,NULL);
	printf("Current time is %s, the milisecond is %d\n",ctime(&mytime.tv_sec));
}


/*
 * Display time out when the signal has been waiting for specific time with in the setitimer() function
 */
void
timeout()
{
	printf("Executed timeout!\n");
	i = i + 1;
	done =1;
}