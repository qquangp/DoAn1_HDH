#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#define length 4
static char kq[length];
int main()
{
int ret,fd;
fd=open("/dev/generator",O_RDWR);//mo device de read
if(fd<0)
{
perror ("Failed to open the device\n");
return errno;
}
printf("Reading from the device\n");//doc random number tu generator
ret=read(fd,kq,length);
if(ret<0)
{
printf("Failed to read from the device\n");
return errno;
}
else
printf("Random number is %s\n",kq);
return 0;
} 
