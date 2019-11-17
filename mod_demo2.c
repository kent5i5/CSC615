/*
** Module demo based on Kernel Projects for Linux, Lab #4 and lkmpg2.6
** To compile:  make -C /usr/src/linux M=`pwd`
** Contents of Makefile:  obj-m := mod_demo2.o
** Use insmod/rmmod to install and remove this module
** To invoke the module read routine use 'cat /proc/testing'
** Look in /var/log/messages for the module output (note that
**   you must 'emerge syslog-ng' and 'rc-update add syslog-ng default'
**   in order for output logging to occur)
**
** This code is based on the mod_demo2 and mod_demo3 provided by 
** by Pf. mmurphy
** I modified the code and have the moduless display the my name 
** and servername in the testing file and the /var/log/messages
**	MCM, 10/8/2005
*/
#include <linux/init.h>	 //This is needed for _init and _exit 
#include <linux/module.h>   //This is needed for kernel programming
#include <linux/kernel.h>   //This is also needed for kernel programming
#include <linux/proc_fs.h>  //This is also needed for process_entry
#include <linux/moduleparam.h>

#include <linux/utsname.h>  //This is needed to support the date structure - utsname()
#include <linux/time.h> // This is needed to support CURRENT_TIME
#define	pfile_name "testing"

MODULE_LICENSE("Dual BSD/GPL");

struct proc_dir_entry *mcm_mod_proc_file;   //a pointer to the /proc 

int
myreader(char *buffer,
	char **buffer_location,
	off_t offset, int buffer_length, int *eof, void *data)
{
	int	ret;
	struct new_utsname *h //create a pointer for utsname();
	h=utsname(); 		//pointed to utsname()

	printk(KERN_ALERT "myreader called\n");
/* see lkmp2.6 for details on the logic here */
/* Since this function calls the read function which doesn't        * have terminated indicator, the modules function has to stop 
* the read function when no data is available or when the buffer
* is full.

	if (offset > 0) {
		//Done with reading , return 0;
		ret = 0;
	} else {
		// This program read this string in one go.
		ret = sprintf(buffer, "HELLO %s on %s: %d, %d!\n", "ying kit ng", h->nodename, (int)CURRENT_TIME.tv_sec,(int)CURRENT_TIME.tv_nsec/1000);    //Here I added my name and the hostname
	}
	return (ret);
}
static int demo_init(void)
{
	struct new_utsname *u //creat a struct pointer
	u=utsname()		//pointed to hostname	

	// print out a message with my name, hostname and the time
	printk(KERN_ALERT "HELLO %s on %s: %d, %d!\n", "ying kit ng", h->nodename, (int)CURRENT_TIME.tv_sec,(int)CURRENT_TIME.tv_nsec/1000);
	mcm_mod_proc_file = create_proc_entry(pfile_name,0644,NULL);
	if (mcm_mod_proc_file == NULL) {
//		remove_proc_entry(pfile_name,&proc_root); &proc_root obsolete!
		remove_proc_entry(pfile_name,NULL);
		printk(KERN_ALERT "Error: create proc entry\n");
		return -ENOMEM;
	}
	/*Initialization of the process
	 * Having the proc_entry pointer to myreader function
	mcm_mod_proc_file->read_proc = myreader;	
//	mcm_mod_proc_file->owner = THIS_MODULE;	owner obsolete!
	mcm_mod_proc_file->mode	= S_IFREG | S_IRUGO; /* copied from lkmp2.6 */
      //Assigne the IDs and size of the process
	mcm_mod_proc_file->uid=0;  
	mcm_mod_proc_file->gid=0;
	mcm_mod_proc_file->size=0;
	printk(KERN_ALERT "/proc/testing created\n");
	return 0;
}
static void demo_exit(void)
{
	printk(KERN_ALERT "mcm:Lab#4 Demo Ending\n");
//	remove_proc_entry(pfile_name,&proc_root); &proc_root obsolete
	remove_proc_entry(pfile_name,NULL);
	printk(KERN_ALERT "/proc/testing removed\n");
}
module_init(demo_init);
module_exit(demo_exit);
