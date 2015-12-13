#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int simple_init(void)
{
  printk(KERN_INFO "Loading Module\n");
  printk(KERN_INFO "%16s%4s%8s\n", "name", "s", "pid");

  struct task_struct *task;
  
  for_each_process(task) {
    printk(KERN_INFO "%16s%4ld%8d\n", task->comm, task->state, task->pid);
  }
  return 0;
}

void simple_exit(void)
{
  printk(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing Task Module");
MODULE_AUTHOR("Apichan");


