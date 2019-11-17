#include <sys/time.h>
#include <time.h>
#include <stdio.h>

main() {
	
}

void 
actual time{
	struct	timeval	mytime;

	gettimeofday(&mytime,NULL);
	printf("%s\n",ctime(&mytime.tv_sec));
}


