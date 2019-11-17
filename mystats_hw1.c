/*
 * 
 */


/*include header*/
#include <errno.h> //errno.h is required for printing out the error message
#include <stdio.h> //stdio.h library is  required for sprinf() function
#include <stdlib.h>  
#include <unistd.h>   //unistd.h is needed for getOpt_long
#include <sys/types.h>
#include <sys/stat.h> 
#include <sys/sysinfo.h> // it is needed for sysinfo
#include <fcntl.h>


/* Part A and B is include in the program of part C
 * Taking a argument which represents a flag to decide
 * whether the program should display additional statistics
 * 
 * part C take the second argument as the flag get additional 
 * information about the computer
 */
int main(int argc[], char* argv[]) {

	char c;
    FILE* pOutput;

	char d;
	FILE* pOutput2;

	struct sysinfo sys_info;
	int day, hour, min;

	struct stat sb;

	int opt;
	int Sec_Opt;
	int duration;
	int longOpt;
	int long_index;

	char mybuf[1000];
	char mybuf2[256];
	char vernum[256];
	char vmstat[256];
	char cpuinfo[10000];
	char flag1;
	long flag2, flag3;

	

	//sysinfo(&info);
	


	//char	input[]="one   two 	three		four";
	int a,b,c,d;

	char	variable1[16];
	char	variable2[16];
	char	variable3[16];
	char	variable4[16];
		
	int fd; //file handle
	int err;
	int count;

	/*The program is Taking three Part A, B,C : mystats -s 1 60 
	if ( (argc != 3) || ((flag1 = argv[1] <= 0) || ((flag2 = atol(argv[2])) <=0) || ((flag3 = atol(argv[2])) <=0) ) {
        	fprintf (stderr, "Usage: %s nprocs \n", argv[0]);
        	exit(-1);
    }

	opt = getOpt(argc, argv, "optional string");
	//while (opt != -1){
		switch(opt){
			case 's':
				break;
			case '':
				break;
			default:
                /* nothing happen 
                break;

		}
		
		opt = getopt( argc, argv, "optional string");
		sec_opt = opt;
		opt = getopt(argc, argv, "optional string")
		duation = opt;
		
	}*/

	/*Extra credit getopt_long replace getopt
	 * man page:
	 * argv is an option argument
	 * longindex points to longopts
	 * 
	 */
	while ((opt = getopt_long(argc, argv, "optional string", longOpt, long_index))!= -1) {
		switch (opt) {
		case 's':
			flag1 = 1;
			break;
		case '2':
		default:
			break;

		}
		
	
		
	}
	opt = getopt_long(argc, argv, "optional string", longOpt, long_index);
	flag2 = opt;  //2sec
	opt = getopt_long(argc, argv, "optional string", longOpt, long_index);
	flag3 = opt;  //peroid = 60sec

	//
	

    system( "uname -a > /tmp/output.txt" );
    
	/*Open the /proc directory to get kernel variables */
	if ((fd = open("/proc/cpuinfo",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	//a =5;
	while ((count = read(fd, &variable1[0], sizeof(variable1))) > 0) {
		
		sscanf(&variable1[0],"model name :  %s",&cpuinfo[0]);
		//write(1, &cpuinfo[0], sizeof(cpuinfo));
		//a--;
		printf("The CPU is :%s\n", &cpuinfo[0]);
	}
	
	if(count < 0) {
		perror ("Bad read");
		exit (-1);
	}


    /*
	pOutput = fopen( "/tmp/output.txt", "r" );
	for( ;; )
    {
        if( fread( &c, 1, 1, pOutput ) )
        {
            putchar( c );
        }
        else
        {
            fclose( pOutput );
            break;
        }
    }*/

	//printf("CPU type = %s, model = %s, number of process = %d\n",info.uptime);

	/*Open the /proc directory to get kernel variables */
	if ((fd = open("/proc/version",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	
	//  display variables
	while ((count = read(fd, &mybuf[0], sizeof(mybuf))) > 0) {
		sscanf(&mybuf[0],"Linux version %s",&vernum[0]);
		//write(1, &vernum[0], sizeof(vernum))
		printf("The version is :%s\n", &vernum[0]);
	}
	if(count < 0) {
		perror ("Bad read");
		exit (-1);
	}

	// print the up time starting from boot time of the server
	if(sysinfo(&sys_info) != 0)
    perror("sysinfo");

  // Uptime
  day = sys_info.uptime / 86400;
  hour = (sys_info.uptime / 3600) - (day * 24);
  min = (sys_info.uptime / 60) - (day * 1440) - (hour * 60);

  printf("Uptime: 0%d:%d:%d:%ld\n",
                      day, hour, min, sys_info.uptime % 60);


	/* open timer_stats and display the info. */
	if ((fd = open("/proc/stat",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	
	while ((count = read(fd3, &mybuf[0], sizeof(mybuf))) > 0) {
	printf("%s NOOOOO",&mybuf[0]); //scan through the file

		

		//write(1, &vmstat[0], sizeof(vmstat));

		

	}
	sscanf(&mybuf[0]," processes%s  %d",&procs1[0], &procs2);

	printf("The number of processes have been created since system last booted is :%s\n",&procs1[0]);   // &vmstat[0]

	if(count < 0) {

		perror ("Bad read");

		exit (-1);

	}


	/*
	 * Part C:
	 * Taking addition option argument -s, if it present, the program display the following
	 * idle.
	 * • The number of disk requests made on the system.
	 * • The number of context switches that the kernel has performed.
	 * • The time when the system was last booted.
	 * • The number of processes that have been created since the system was booted.
	 */

	
	/* time spending on user mode, system mode, idle : cpu normal user nice user kernel idle (in the stat file)  */
	if ((fd = open("/proc/stat",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	
	while ((count = read(fd3, &mybuf[0], sizeof(mybuf))) > 0) {
	printf("%s NOOOOO",&mybuf[0]); //scan through the file

		

		//write(1, &vmstat[0], sizeof(vmstat));

		

	}
	sscanf(&mybuf[0]," processes%s  %d",&procs1[0], &procs2);

	printf("The number of processes have been created since system last booted is :%s\n",&procs1[0]);   // &vmstat[0]

	if(count < 0) {

		perror ("Bad read");

		exit (-1);

	}


	
	printf("Preferred I/O block size: %ld bytes\n",
            (long) sb.st_blksize);
   // printf("File size:                %lld bytes\n",
    //        (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n",
            (long long) sb.st_blocks);

	printf("so the disk size will be block size times number of block = %ld\n", (long)sb.st_blksize );
	// free memory on the CPU
  printf("Total Ram: %ldk\tFree: %ldk\n", sys_info.totalram / 1024,
                                        sys_info.freeram / 1024);

  // Shared and buffered ram.
  printf("Shared Ram: %ldk\n", sys_info.sharedram / 1024);
  printf("Buffered Ram: %ldk\n", sys_info.bufferram / 1024);


  /*
  system( "vmstat > /tmp/output.txt" );
  pOutput2 = fopen( "/tmp/output.txt", "r" );
	for( ;; )
    {
        if( fread( &d, 1, 1, pOutput2 ) )
        {
            putchar( d );
        }
        else
        {
            fclose( pOutput );
            break;
        }
    }*/








	exit (-1);
	//if (){
	
//	}

}