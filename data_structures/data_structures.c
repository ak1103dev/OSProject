#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
  int day;
  int month;
  int year;
  struct list_head list;
};

static LIST_HEAD(birthday_list);

int simple_init(void)
{
  struct birthday *person1;
  person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
  person1->day = 2;
  person1->month = 8;
  person1->year = 1995;
  INIT_LIST_HEAD(&person1->list);
  list_add_tail(&person1->list, &birthday_list);

  struct birthday *person2;
  person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
  person2->day = 3;
  person2->month = 7;
  person2->year = 1996;
  list_add_tail(&person2->list, &birthday_list);

  struct birthday *person3;
  person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
  person3->day = 4;
  person3->month = 6;
  person3->year = 1997;
  list_add_tail(&person3->list, &birthday_list);

  struct birthday *person4;
  person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
  person4->day = 5;
  person4->month = 5;
  person4->year = 1998;
  list_add_tail(&person4->list, &birthday_list);

  struct birthday *person5;
  person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
  person5->day = 6;
  person5->month = 4;
  person5->year = 1999;
  list_add_tail(&person5->list, &birthday_list);

  printk(KERN_INFO "Loading Module\n");

  struct birthday *person;
  list_for_each_entry(person, &birthday_list, list) {
    printk(KERN_INFO "%d, %d, %d\n", person->day, person->month, person->year);
  }
  return 0;
}

void simple_exit(void)
{
  struct birthday *ptr, *next;
  
  list_for_each_entry_safe(ptr, next, &birthday_list, list) {
    list_del(&ptr->list);
    kfree(ptr);
  }
  printk(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Data Structure Module");
MODULE_AUTHOR("Apichan");
