#include <stdio.h>
#include <sys/time.h>
#include <signal.h>


main()
{
	int	n;
	char	buf[1];
	void 	timeout();
	struct	itimerval	myvalue,myovalue;

//siginterrupt(SIGALRM,1);
	printf("Setting signal handler\n");
	if ((signal(SIGALRM, timeout)) == SIG_ERR) {
		printf("Error in setting signal handler\n");
		exit(-1);
	}

	printf("Clearing timer\n");
	timerclear(&myvalue.it_interval);
	timerclear(&myvalue.it_value);
	timerclear(&myovalue.it_interval);
	timerclear(&myovalue.it_value);
	if (( n = setitimer(ITIMER_REAL,&myvalue,&myovalue)) < 0 ) {
		printf("Error in clearing timer\n");
		exit(-1);
	}

	printf("Setting timer\n");
	myvalue.it_value.tv_sec = 3; /* timeout interval in seconds */
		/* set tv_usec for millesecond timeout */
	if (( n = setitimer(ITIMER_REAL,&myvalue,&myovalue)) < 0 ) {
		printf("Error in clearing timer\n");
		exit(-1);
	}

	printf("Waiting for signal...\n");
/*	for(;;);
 *	*/
	printf("going to sleep\n");
	n = read (0,&buf,1); 
	printf("woke up after read!\n");
}
void
timeout()
{
	printf("Executed timeout!\n");
}
