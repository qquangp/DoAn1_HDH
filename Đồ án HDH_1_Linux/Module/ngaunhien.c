#include <linux/module.h>
#include <linux/random.h>
#include <linux/kernel.h>
#include <linux/init.h>
#define DRIVER_AUTHOR "Le Hong Quang Nguyen Dinh Thao"
#define DRIVER_DESC "A linux kernel module for a random number"
#define NUM 10
void get_random_bytes(void *buf,int nbytes);
static int init_random(void)
{
unsigned long rnum;
get_random_bytes(&rnum,sizeof(unsigned long));
printk("The random number is %ld\n",rnum);
return 0;
}

static void  exit_random(void)
{
printk("Goodbye\n");
}


module_init(init_random);
module_exit(exit_random);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("testdevice");

