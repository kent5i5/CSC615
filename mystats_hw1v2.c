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

	char mybuf[970];
	char mybuf2[66];
	char mybuf3[256];
	char mybuf4[256];
	char mybuf5[30];
	char ctxt[400];
	char diskstat[400];
	char meminfo[200];

	char vernum[256];
	char vmstat[256];
	char cpuinfo[256];
	int flag1;
	int flag2;

	

	//sysinfo(&info);
	


	//char	input[]="one   two 	three		four";
	int a,e, f,g, h, i , j , k;

	//cpu info variables
	char	variable1[16];
	char	variable2[16];
	char	variable3[16];
	char	variable4[16];
	char	variable5[16];
	char	variable6[16];
	char	variable7[16];
		
	//#proccesses variables
	char procs1[16];
	int procs2;
	char procs3[16];
	int procs4;

	//#amount time spends for cpu
	int t,t1,t2,t3, t4 , t5;

	//context switch
	int ct;

	//boot time 
	int bt;
	
	//disk info
	int rd , wt, dk;

	//total memory 
	char mem[16];
	int mem2;
	char fmem[16];
	int fmem2;

	//free memory 

	//

	//file handles
	int fd, fd2, fd3, fd4, fd5, fd6; 
	long arg1, arg2;   //  grab the sec/period: 2 60 
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
	flag1 = 0;
	flag2 = 0;
	while ((opt = getopt_long(argc, argv, "optional string", longOpt, long_index))!= -1) {
		switch (opt) {
		case 's':
			flag1 = 1;
			break;
		case 'l':
			flag2 = 1;
			//if ( (argc != 4) || (( arg1 = atol(argv[3])) <= 0) || ((arg2 = atol(argv[4])) <=0)  ) {
        	//	fprintf (stderr, "Usage: %s nprocs \n", argv[0]);
        	//	exit(-1);
			//}
		default:
			break;

		}
		
	
		
	}
	opt = getopt_long(argc, argv, "optional string", longOpt, long_index);
	arg1 = opt;   //2sec
	opt = getopt_long(argc, argv, "optional string", longOpt, long_index);
	arg2 = opt;  //peroid = 60sec

	//
	

    system( "uname -a > /tmp/output.txt" );
    
	/*Open the /proc directory to get kernel variables */
	if ((fd = open("/proc/cpuinfo",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	
	//skip to model name
	count = read(fd, &mybuf2[0], sizeof(mybuf2));
	//printf("%s NOOO\n", &mybuf2[0]);
	count = read(fd, &mybuf2[0], sizeof(mybuf2));
	//printf("%s NOOO\n", &mybuf2[0]);
	
	sscanf(&mybuf2[0],"model name %s %s %s %s %s %s %s",&variable1[0],&variable2[0],&variable3[0], &variable4[0], &variable5[0], &variable6[0],&variable7[0]);
		//write(1, &cpuinfo[0], sizeof(cpuinfo));
		
		printf("The CPU is %s %s %s %s %s %s %s\n",&variable1[0],&variable2[0], &variable3[0], &variable4[0], &variable5[0], &variable6[0], &variable7[0]);
	if(count < 0) {
		perror ("Bad read");
		exit (-1);
	}


   

	//printf("CPU type = %s, model = %s, number of process = %d\n",info.uptime);

	/*Open the /proc directory to get kernel variables */
	if ((fd2 = open("/proc/version",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	
	//  display variables
	while ((count = read(fd2, &mybuf3[0], sizeof(mybuf3))) > 0) {
		sscanf(&mybuf3[0],"Linux version %s",&vernum[0]);
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


	
  if ( flag1 > 0 )  {

	/*
	 * Part C:
	 * Taking addition option argument -s, if it present, the program display the following
	 * idle.
	 * • The number of disk requests made on the system.
	 * • The number of context switches that the kernel has performed.
	 * • The time when the system was last booted.
	 * • The number of processes that have been created since the system was booted.
	 */

	
  /*The amount of time that the CPU has spent in user mode, in system mode and idle
  printf("       us: Time spent running non-kernel code. (user time, including nice time)");
  printf("      sy: Time spent running kernel code. (system time) ");
  printf("     id: Time spent idle. Prior to Linux 2.5.41, this includes IO-wait time.");
  printf("     wa: Time spent waiting for IO. Prior to Linux 2.5.41, included in idle.");
  printf("     st: Time stolen from a virtual machine. Prior to Linux 2.6.11, ");
	
	 printf(" us  sy  id  wa  st ");*/

	/* time spending on user mode, system mode, idle : cpu normal user nice user kernel idle (in the stat file)  */
	if ((fd5 = open("/proc/stat",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	
	//while ((count = read(fd5, &mybuf5[0], sizeof(mybuf5))) > 0) {
	//printf("%s NOOOOO",&mybuf5[0]); //scan through the file

		
	count = read(fd5, &mybuf5[0], sizeof(mybuf5));
		//write(1, &vmstat[0], sizeof(vmstat));
	sscanf(&mybuf5[0]," cpu %d %d %d %d %d",&t1, &t2, &t3, &t4, &t5);
	t = t1 +t2;
	printf(" Time spending on user-mode, system-mode, idle-time   \n");
	printf("CPU :              %d        %d      %d\n",t,t3,t4);   // &vmstat[0]
	
	if(count < 0) {

		perror ("Bad read");

		exit (-1);

	}

	/* continue to grab the ctxt(#context switch) info from stat file */
	while ((count = read(fd5, &ctxt[0], sizeof(ctxt))) > 0) {
	
		
		//write(1, &vmstat[0], sizeof(vmstat));
		
		
	}
	count = read(fd5, &ctxt[0], sizeof(ctxt));
	//printf("%s NOOOOO",&ctxt[0]); //scan through the file
	//sscanf(&ctxt, "@%[^\n]", ct);  %*[^-]
	//sscanf(&ctxt[0]," %*d %*d %*d %*d %*d %*d ctxt %d",&ct);
	sscanf(&ctxt[0],"%*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d\nctxt %d\n",&ct);
	printf("The number of context switches :%d\n",ct);   // &vmstat[0

	//count = read(fd5, &btime[0], sizeof(btime));
	sscanf(&ctxt[0],"%*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d\n%*s %*d\nbtime %d",&bt);
	printf("The number boot time is :%d\n",bt);   // &vmstat[0
	if(count < 0) {
		perror ("Bad read");
		exit (-1);
	}
	

	/* open diskstats and read the number of read and write and find the number ofdisk requests. */
	if ((fd3 = open("/proc/diskstats",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	
	while ((count = read(fd3, &mybuf[0], sizeof(mybuf))) > 0) {
		//scan through the file
		//write(1, &vmstat[0], sizeof(vmstat));

	}
	//printf("%s NOOOOO",&mybuf[0]); //scan through the file
	sscanf(&mybuf[0],"%*d %*d %*d %*d sda %d %*d %*d %*d %d", &rd, &wt);
	dk = rd+ wt;
	printf("The number of disk request is: %d+%d = %d \n",rd, wt, dk);   // &vmstat[0]
	if(count < 0) {
		perror ("Bad read");
		exit (-1);
	}

	/* open timer_stats and display the #process since last boot. */
	//if ((fd3 = open("/proc/stat",O_RDONLY))<0){  // Here is the kernel version 
	//	perror("open file error");
	//	exit(-1);
	//}
	
	//count = read(fd5, &mybuf[0], sizeof(mybuf));
	//printf("%s NOOOOO",&mybuf[0]); //scan through the file
	sscanf(&ctxt[0],"%*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*s %*d %*s %*d processes %d", &procs2);
	printf("The number of processes have been created since system last booted is: %d\n",procs2);   // &vmstat[0]
	if(count < 0) {
		perror ("Bad read");
		exit (-1);
	}
}
/***  End of Part C  */

if (flag2 > 0){
	//printf("a1 %ld, a2 %ld\n",arg1,arg2);
	/*
	 * Part D- extra credit
	 * • The amount of memory configured into the computer
	 * • The amount of memory currently available
	 * • A list of load averages (each averaged over the last minute). These are
	 * calculated
	 */
	/* open timer_stats and display the #process since last boot. */
	if ((fd6 = open("/proc/meminfo",O_RDONLY))<0){  // Here is the kernel version 
		perror("open file error");
		exit(-1);
	}
	//total memory
	count = read(fd6, &meminfo[0], sizeof(meminfo));
	//printf("%s NOOOOO\n",&meminfo[0]); //scan through the file
	sscanf(&meminfo[0],"MemTotal: %d %s",&mem2,&mem[0]);
	printf("The total memory is :  %d %s \n",mem2, &mem[0]);   // &vmstat[0]

	//free memory
	sscanf(&meminfo[0],"%*s %*d %*s\nMemFree: %d %s",&fmem2,&fmem[0]);
	printf("The free memory is :  %d %s \n",fmem2, &fmem[0]);   // &vmstat[0]
	if(count < 0) {
		perror ("Bad read");
		exit (-1);
	}
	

}
/*** End of Part D*/

	exit (-1);
	

}
