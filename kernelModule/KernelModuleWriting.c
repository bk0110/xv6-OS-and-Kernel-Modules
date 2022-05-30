#include <linux/module.h> /* need to include for every kernel module */
#include <linux/kernel.h> /* used it only for printk log levels */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Preeti");
MODULE_DESCRIPTION("A simple module which prints KERNEL MODULE LOADED message when loaded and KERNEL MODULE REMOVED when unloaded from kernel");


int init_module(void)
{
	printk(KERN_INFO "Kernel Module Loaded\n");/*KERN_INFO priority = 6 , current console log level = 4*/
	
	return 0;
	
	/* 0 is returned when module is successfully loaded, in case of an error--> o will not be returned*/
}

void cleanup_module(void)
{
	printk(KERN_INFO "Kernel Module Removed\n");
}

