#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/random.h>
#define DRIVER_AUTHOR "Le Hong Quang Nguyen Dinh Thao"
#define DRIVER_DESC "A character device driver for random number"
#define DRIVER_VERSION "0.1"
#define device_name "generator"
#define class_name "random"
static int majornum;//device number
static struct class *ranclass=NULL;
static struct device *randevice=NULL;
static unsigned char rannum;
static char temp[4]={'\0'};
static int i=0;
static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*,struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t *);
static struct file_operations fops =
{
.open=dev_open,
.read=dev_read,
.release=dev_release,
};
static int __init chardevran_init(void)
{
majornum=register_chrdev(0,device_name,&fops);
if(majornum<0)
{
printk("Failed to register a major number\n");
goto failed_register_majnum;
}
printk("The major number is %d\n",majornum);
//register device class
ranclass=class_create(THIS_MODULE,class_name);
if(IS_ERR(ranclass))//kiem tra loi
{
unregister_chrdev(majornum,device_name);
printk("Failed to register device class\n");
goto failed_register_class;
}
//register the device driver
randevice=device_create(ranclass,NULL,MKDEV(majornum,0),NULL,device_name);
if(IS_ERR(randevice))
{
class_destroy(ranclass);
unregister_chrdev(majornum,device_name);
printk("Failed to create the device\n");
goto failed_register_driver;
}
printk("Successfully to create a device class\n");
return 0;
failed_register_majnum:
return majornum;
failed_register_class:
return PTR_ERR(ranclass);
failed_register_driver:
return PTR_ERR(randevice);
}
static void __exit chardevran_exit(void)
{
device_destroy(ranclass,MKDEV(majornum,0));//remove device
class_unregister(ranclass);//unregister device
class_destroy(ranclass);//remove class
unregister_chrdev(majornum,device_name);//unregister major number
printk("Goodbye\n");
}
//inodep is pointer to an inode object
//filep is pointer to a file object
static int dev_open(struct inode *inodep, struct file *filep)
{
printk("Device is opening\n");
return 0;
}
//this function to read from user space  and data is sent from device to user
static ssize_t dev_read(struct file *filep,char *buffer, size_t len,loff_t *offset)
{
i=0;
get_random_bytes(&rannum,sizeof(char));
printk("Random number is %d\n",rannum);
if(len<4)
{
printk("Failed\n");
return -EFAULT;
}
if(rannum!=0)
{
while(rannum!=0)
{
temp[i]=rannum%10+'0';
rannum=rannum/10;
i++;
}
temp[i]='\0';
buffer[i]='\0';
i-=1;
while(i>=0)
{
*buffer=temp[i];
i-=1;
buffer+=1;
}
return 0;
}
else
{
*(buffer++)='0';
*buffer ='\0';
return 0;
}
}
static int dev_release(struct inode *inodep, struct file *filep)
{
printk("Device successfully closed\n");
return 0;
}
module_init(chardevran_init);
module_exit(chardevran_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
MODULE_SUPPORTED_DEVICE("testdevice");

