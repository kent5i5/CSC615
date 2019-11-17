/*
** Module demo based on Kernel Projects for Linux, Lab #4 and lkmpg2.6
** To compile:  make -C /usr/src/linux M=`pwd`
** Contents of Makefile:  obj-m := myclock2.o 
** (change the Makefile in /sys/kernel, skip: make menuconfig)
** Use insmod/rmmod to install and remove this module
** To invoke the module read routine use 'cat /proc/testing'
** I removed this output:
** [Look in /var/log/messages for the module output (note that
**   you must 'emerge syslog-ng' and 'rc-update add syslog-ng default'
**   in order for output logging to occur)]
**
**	MCM, 10/8/2005
** This code is based on the mod_demo2 provided by Pf. murphy
** 
** I modified it and remove the output in /var/log/message, the modules
** returns a string of second and millisecond of current time using 
** proc peudofile. When a process call the read(), the string of time
** (sec&millisec/1000 separated by a single empty space) will be return . 
** The User interface process reformat the time from the /proc/myclock, and 
** display it once per sec over a 5 minutes period.
**
** This modules now also create a myclock2 subdirecotry in sysf
** called /sys/kernel/kobject_myclock2 where the myclock2 file is created.
** I can put a integer into the file and modules begin the count down 
** when timeout, it sends signal back to the user interface and interrupt 
** the process. This modules is based on the demo provided by pf. mmurphy
**
** for hw6, I simply make an array of size 10 for inputs and my_timer. I 
** count the number inputs and timer, so I can iterate the array and display
** a correct output.
** link: dbsystems.sfsu.edu/~csc615/Assignments/demos/New Lab%235 Demos/
*/
#include <linux/kobject.h>	  //Needed for kobject
#include <linux/string.h>
#include <linux/init.h>           //This is needed to support _init and _exit macro
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>	  //This is needed to support kobjects
#include <linux/proc_fs.h>        //This is needed to support proc_entry
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <asm/siginfo.h>	//it is used to support siginfo struct
//#include <linux/time.h>          // This is needed to support CURRENT_TIME
#include <linux/timer.h>	//This provides support timer of kernel
#include <linux/unistd.h>
#include <linux/jiffies.h>

#define	pfile_name "myclock2"     // This create a text file called myclock in proc directory
#define SIG_TEST 44

static int ntimer =0;
static int inputs[10];
static int cbc=0;
static int inputcount=0;
static int foo;  
static struct timer_list my_timer[10];
static struct timer_list my_timer2;

struct siginfo info[10];		
static struct task_struct *t;

MODULE_LICENSE("Dual BSD/GPL");

/**
 * This structure contains information about the /proc file
 */
struct proc_dir_entry *mcm_mod_proc_file;

void my_timer_callback(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[0].si_signo=SIG_TEST;		//connect it to the real signal
	info[0].si_code=SI_QUEUE;
	info[0].si_int=inputs[cbc];
	cbc++;
	ret=send_sig_info(SIG_TEST, &info[0],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}//end of callback 1

void my_timer_callback1(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[1].si_signo=SIG_TEST;		//connect it to the real signal
	info[1].si_code=SI_QUEUE;
	info[1].si_int=inputs[1];
	ret=send_sig_info(SIG_TEST, &info[1],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}//end of callback1

void my_timer_callback2(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[2].si_signo=SIG_TEST;		//connect it to the real signal
	info[2].si_code=SI_QUEUE;
	info[2].si_int=inputs[2];
	ret=send_sig_info(SIG_TEST, &info[2],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}//callback2

void my_timer_callback3(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[3].si_signo=SIG_TEST;		//connect it to the real signal
	info[3].si_code=SI_QUEUE;
	info[3].si_int=inputs[3];
	ret=send_sig_info(SIG_TEST, &info[3],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}//callback3

void my_timer_callback4(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[4].si_signo=SIG_TEST;		//connect it to the real signal
	info[4].si_code=SI_QUEUE;
	info[4].si_int=inputs[4];
	ret=send_sig_info(SIG_TEST, &info[4],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}//callback4

void my_timer_callback5(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[5].si_signo=SIG_TEST;		//connect it to the real signal
	info[5].si_code=SI_QUEUE;
	info[5].si_int=inputs[5];
	ret=send_sig_info(SIG_TEST, &info[5],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}//callback5

void my_timer_callback6(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[6].si_signo=SIG_TEST;		//connect it to the real signal
	info[6].si_code=SI_QUEUE;
	info[6].si_int=inputs[6];
	ret=send_sig_info(SIG_TEST, &info[6],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}//callback6

void my_timer_callback7(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[7].si_signo=SIG_TEST;		//connect it to the real signal
	info[7].si_code=SI_QUEUE;
	info[7].si_int=inputs[7];
	ret=send_sig_info(SIG_TEST, &info[7],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}//callback7

void my_timer_callback8(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[8].si_signo=SIG_TEST;		//connect it to the real signal
	info[8].si_code=SI_QUEUE;
	info[8].si_int=inputs[8];
	ret=send_sig_info(SIG_TEST, &info[8],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}

void my_timer_callback9(unsigned long data)
{
	int ret;
	
	//below is debug output
	printk("kobject_mcm: my_timer_callback called, send signal to pid %d\n", t->pid);
	
	//set up the signal
	memset(&info, 0, sizeof(struct siginfo));
	info[9].si_signo=SIG_TEST;		//connect it to the real signal
	info[9].si_code=SI_QUEUE;
	info[9].si_int=inputs[9];
	ret=send_sig_info(SIG_TEST, &info[9],t);
	if(ret < 0){
		printk("kobject_mcm: error sending signal\n");
	}
}



/*  
 * The "foo" file where a static varible, which is an integer,
 * is read form and written to
 */
static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
		 char *buf)
{
	int ret=0;
	printk("kobject_mcm(foo_show): pid=%d, foo=%d\n", current->pid, foo); 	
	t = current;
	//set up the timer
	printk("kobject_mcm: starting timer to fire in %d seconds\n", foo);
	
	//if (ntimer == 0)
		ret = mod_timer(&my_timer[ntimer],jiffies+msecs_to_jiffies(foo*1000));
	//if (ntimer == 1)
	//	ret = mod_timer(&my_timer[1], jiffies+msecs_to_jiffies(foo*1000));	

	if (ret) printk("kobject_mcm:error in setting timer\n");

	ntimer++;
	printk("number of timer %d \n", ntimer);
	return sprintf(buf, "%d\n", foo);
}

/*
 * The foo_store put the input value in the foo file.
 */
static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%du", &foo);
	inputs[inputcount] = foo;
	inputcount++;
	//printk is debugging output
	printk("kobject_mcm(foo_store): pid=%d, foo=%d\n", current->pid, foo);	

	return count;
}

static struct kobj_attribute foo_attribute =
		 __ATTR(foo, 0666, foo_show, foo_store);

/*
 * Create a group of attribute so that we can create and destory them all once
 */ 
static struct attribute *attrs[] = {
	&foo_attribute.attr,
	NULL, /* NULL to terminate the list of attributes*/
};

/*
 * An unnamed attribute group will put all of the attributes directly in the 
 * kobject directory. If we specify a name, a subdirectory will be created for
 * the attributes with the directory being the name of the attribute group.
 */
static struct attribute_group attr_group = {
	.attrs = attrs,
};

static struct kobject *myclock2_kobj;

/**
 * 
 */
int
myclockreader(char *buffer,
	char **buffer_location,
	off_t offset, int buffer_length, int *eof, void *data)
{
	int	ret;

	printk(KERN_ALERT "myclock called\n");
/* see lkmp2.6 for details on the logic here 
 * Based on the explanation in lkmpg2.6, the function basely read all 
 * information at once and return the size of the buffer. it prevents 
 * the library from keep calling the function when there are no more data.
 */
	if (offset > 0) {
		ret = 0;
	} else {
		ret = sprintf(buffer, "%d %d\n",(int)CURRENT_TIME.tv_sec, (int)CURRENT_TIME.tv_nsec/1000);
	}
	return (ret);
}

static int __init myclock2_init(void)
{  	
	int retval;	
	setup_timer(&my_timer[1], my_timer_callback, 0);
	setup_timer(&my_timer[2], my_timer_callback, 0);
	setup_timer(&my_timer[3], my_timer_callback, 0);
	setup_timer(&my_timer[4], my_timer_callback, 0);
	setup_timer(&my_timer[5], my_timer_callback, 0);
	setup_timer(&my_timer[6], my_timer_callback, 0);
	setup_timer(&my_timer[7], my_timer_callback, 0);
	setup_timer(&my_timer[8], my_timer_callback, 0);
	setup_timer(&my_timer[9], my_timer_callback, 0);
	setup_timer(&my_timer[0], my_timer_callback, 0);
	
	setup_timer(&my_timer2, my_timer_callback, 0);

	printk(KERN_ALERT "%d %d\n",(int)CURRENT_TIME.tv_sec, (int)CURRENT_TIME.tv_nsec/1000);
	
	mcm_mod_proc_file = create_proc_entry(pfile_name,0644,NULL);
	if (mcm_mod_proc_file == NULL) {
//		remove_proc_entry(pfile_name,&proc_root); &proc_root obsolete!
		remove_proc_entry(pfile_name,NULL);
		printk(KERN_ALERT "Error: create proc entry\n");
		return -ENOMEM;
	}
	mcm_mod_proc_file->read_proc = myclockreader;	
//	mcm_mod_proc_file->owner = THIS_MODULE;	owner obsolete!
	mcm_mod_proc_file->mode	= S_IFREG | S_IRUGO; /* copied from lkmp2.6 */
	mcm_mod_proc_file->uid=0;
	mcm_mod_proc_file->gid=0;
	mcm_mod_proc_file->size=0;
	printk(KERN_ALERT "/proc/testing created\n");

	/*
 	 * Create a simple kobject with the name of "myclock2",
	 * located under /sys/kernel
	 * 
	 * As this is a simple directory , no uevent will be sent to userspace.
	 * This function should not be used for any type of dynamic kobjects, 
	 * where the name and number are not known ahead of time.
	 */
	myclock2_kobj = kobject_create_and_add("myclock2", kernel_kobj);
	if (!myclock2_kobj)
		return -ENOMEM;

	/* Create the files associated with this kobject
	 * sysfs_create_group allows more extentibilty 
	 * for next assignment
         */
	retval = sysfs_create_group(myclock2_kobj, &attr_group);
	if (retval)
		kobject_put(myclock2_kobj);
	printk("kobject_mcm: Initialized timer & kobject\n");
	return retval;
}
static void __exit myclock2_exit(void)
{
	int ret;
	ret = del_timer(&my_timer[0]);
	ret = del_timer(&my_timer[1]);
	ret = del_timer(&my_timer[2]);
	ret = del_timer(&my_timer[3]);
	ret = del_timer(&my_timer[4]);
	ret = del_timer(&my_timer[5]);
	ret = del_timer(&my_timer[6]);
	ret = del_timer(&my_timer[7]);
	ret = del_timer(&my_timer[8]);
	ret = del_timer(&my_timer[9]);

	ret = del_timer(&my_timer2);

	if (ret) printk("kobject_mcm: The timer is still in use");
	printk("Kobject_mcm: uninstalling\n");

	//release the proc file first
	printk(KERN_ALERT "mcm:Lab#4 Demo Ending\n");
//	remove_proc_entry(pfile_name,&proc_root); &proc_root obsolete
	remove_proc_entry(pfile_name,NULL);
	printk(KERN_ALERT "/proc/testing removed\n");

	/* Release the memory space*/
	kobject_put(myclock2_kobj);	//release the memory
	
}
module_init(myclock2_init);
module_exit(myclock2_exit);
