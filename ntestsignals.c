#include <stdio.h>
#include <sys/time.h>
#include <signal.h>


main()
{
	int	n;
	void 	timeout();
	struct	itimerval	myvalue,myovalue;


	printf("Setting signal handler\n");
	if ((signal(SIGALRM, timeout)) == SIG_ERR) {
		printf("Error in setting signal handler\n");
		exit(0);
	}

	printf("Clearing timer\n");
	timerclear(&myvalue.it_interval);
	timerclear(&myvalue.it_value);
	timerclear(&myovalue.it_interval);
	timerclear(&myovalue.it_value);
	if (( n = setitimer(ITIMER_REAL,&myvalue,&myovalue)) < 0 ) {
		printf("Error in clearing timer\n");
		exit(0);
	}

	printf("Setting timer\n");
	myvalue.it_value.tv_sec = 3; /* timeout interval in seconds */
		/* set tv_usec for microsecond timeout */
	if (( n = setitimer(ITIMER_REAL,&myvalue,&myovalue)) < 0 ) {
		printf("Error in clearing timer\n");
		exit(0);
	}

	printf("Waiting for signal...\n");
	for(;;);
}
void
timeout(int	arg)
{
	printf("Executed timeout!\n");
	exit(0);
}
