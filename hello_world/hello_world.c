#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/vermagic.h>
#include <linux/version.h>
#include <linux/moduleparam.h>

#define KERNEL_DRIVERS_MAJOR    2
#define KERNEL_DRIVERS_MINOR    6
#define KERNEL_DRIVERS_RELEASE 10

//static char *string = "Dummy text."
static int count =  1;
module_param(count, int, S_IRUGO);
static int array[] = {0,0,0,0,0};
module_param_array(array, int, NULL, S_IRUGO);
//module_param(string, charp, S_IRUGO);

static int __init hello_init(void)
{
    int i=0;

#if LINUX_VERSION_CODE == KERNEL_VERSION(KERNEL_DRIVERS_MAJOR, \
					 KERNEL_DRIVERS_MINOR, \
					KERNEL_DRIVERS_RELEASE)
    printk(KERN_ALERT "This module was intended for your kernel: %s.\n", UTS_RELEASE);
#else
    printk(KERN_ALERT "This module was not intended for your kernel: %s.\n", UTS_RELEASE);
#endif

    printk(KERN_ALERT "Running in the process %s (%i).\n", current->comm, current->pid);

    printk(KERN_ALERT "Array of count %i: ", count);
    if (count > ARRAY_SIZE(array))
        count = ARRAY_SIZE(array);
    for (i=0; i<count; i++)
        printk(KERN_ALERT "%i ", array[i]);
    printk(KERN_ALERT " .\n");
    printk(KERN_ALERT "Module initiated!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Module exited.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Andrei Gherzan <andrei@gherzan.ro>");
