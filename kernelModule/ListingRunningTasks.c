#include <linux/module.h> /* need to include for every kernel module */
#include <linux/kernel.h> /* used it only for macro expansion for printk log level, KERN_ALERT */
#include <linux/sched.h>
#include <linux/sched/signal.h>/*in order to use for_each_process to iterate over all the tasks*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Preeti");
MODULE_DESCRIPTION("A simple module which prints all the currently running tasks in Linux System.");


char * task_state(long state)
{

    switch (state) {
        case TASK_RUNNING:
            return "TASK_RUNNING";
    
        default:
        {
            
            return "TASK_NOT_RUNNING";
        }
    }
}
int init_module(void)
{
	
	struct task_struct *task; // Pointer to Stask

  	for_each_process(task)
  	{
  		
  		if(strcmp(task_state(task->state), "TASK_RUNNING") == 0){   /* picking only the processes which are running*/
  		printk( KERN_INFO "task_command: %s | state: %ld | process_id: %d\n", task->comm, task->state, task->pid );
  		}
    		/*printk( KERN_INFO "task_command: %s | state: %ld | process_id: %d \n", task->comm, task->state, task->pid);*/
    		
  	}
  	
	return 0;
	
	/* 0 is returned when module is successfully loaded */
}

void cleanup_module(void)
{
	printk(KERN_INFO "ListingRunningTasks Kernel Module Removed\n");
}

