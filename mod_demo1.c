/*
** Demo based on Linux Kernel Modules 3rd Edition example
** To compile:  make -C /usr/src/linux M=`pwd`
** Contents of Makefile:  obj-m := mod_demo1.o
** Use insmod/rmmod to install and remove this module
** Look in /var/log/messages for the module output (note that
**   you must 'emerge syslog-ng' and 'rc-update add syslog-ng default'
**   in order for output logging to occur)
**
**	MCM, 10/8/2005
*/
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	printk(KERN_ALERT "Hello CSC 615!\n");
	return(0);
}
static void hello_exit(void)
{
	printk(KERN_ALERT "Goodby from the CSC 615 demo #1 module\n");
}
module_init(hello_init);
module_exit(hello_exit);
