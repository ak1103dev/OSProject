#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

#define MAX_DEPT 100
void dfs(struct task_struct *task, int d) {

  struct task_struct *child_task;
  struct list_head *list;

  printk(KERN_INFO "%16s%4ld%8d <parent>\n", task->comm, task->state, task->pid);

  list_for_each(list, &task->children)
  {
    child_task = list_entry(list, struct task_struct, sibling);

    printk(KERN_INFO "%16s%4ld%8d\n", child_task->comm, child_task->state, child_task->pid);

    dfs(child_task, d+1);
  }
}

int simple_init(void) {
  printk(KERN_INFO "Loading Module\n");
  printk(KERN_INFO "%16s%4s%8s\n", "name", "s", "pid");

  dfs(&init_task, 0);

  return 0;
}

void simple_exit(void) {
  printk(KERN_INFO "Removed Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DFS Tree Tasks Module");
MODULE_AUTHOR("Apichan");
