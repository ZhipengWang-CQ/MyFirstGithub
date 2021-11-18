#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
struct appbuffer
{
	unsigned long base;//基准地址
	unsigned long size;//寄存器大小
	unsigned long offset;//偏移值
	unsigned int pos;//向左移动几位
	unsigned int data;//需要替换的值 0/1
	unsigned int value;//修改后寄存器的值
};

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	struct appbuffer *arg = NULL;
    arg = (struct appbuffer *)malloc(sizeof(struct appbuffer));
    if(!arg)
    {
        printf("malloc failed\n");
        return -1;
    }

	//读数据只需要前三个数据
	arg->base = 0x00A00000;//0x01C20800
	arg->size = 32;//32
	arg->offset = 0x00;//0x74
	fd = open("/dev/reg_drv",O_RDWR);
	if(!fd)
	{
		printf("open file failed\n");
		return -1;
	}
	int cmd = atoi(argv[1]);
	if(cmd == 100)
	{
		//读寄存器中的数据
		ret = ioctl(fd,cmd,arg);
		if(ret == -1)
		{
			printf("ioctl error!\n");
			return -1;
		}  
		printf("value = 0x%08X", arg->value);
	}
	else if(cmd = 101 )
	{
		//写寄存器中的数据
		ret = ioctl(fd,cmd,arg);
		if(ret == -1)
		{
			printf("ioctl error!\n");
			return -1;
		} 
		printf("value = 0x%08X", arg->value); 	
	}
	free(arg);
	close(fd);
	return 0;
}