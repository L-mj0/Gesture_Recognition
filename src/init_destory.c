#include "main.h"

//项目程序初始化
int project_init()
{
    //打开LCD文件
    fd_lcd = open("/dev/fb0", O_RDWR);
    if(fd_lcd == -1) return -1;

    //内存映射
    /*LCD屏幕映射到p_lcd*/
    p_lcd = mmap(NULL, PIXELS*4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);//不强转int*会出现段错误
    if(*p_lcd == -1)
    {
        perror("LCD mmap failed!\n");
        return -1;
    }

    //打开触摸屏文件
    fd_touch = open("/dev/input/event0", O_RDONLY);
    if (fd_touch == -1)
    {
        perror("Open touch screen failed!\n");
        return -1;
    }
    
    //创建管道文件
    if(access(FIFO_PATH, F_OK))// 默认管道文件创建在根目录  F_OK:判断是否存在
	{
		//如果没有创建
        int ret_val = mkfifo(FIFO_PATH, 0666);//创建管道文件函数
        if(ret_val < 0) perror("mkfifo error");
        printf("管道文件创建成功\n");
	}
	fd_fifo = open(FIFO_PATH, O_RDWR);
	if(fd_fifo == -1)
	{
		printf("创建管道文件失败！\n");
		return -1;
	}
    return 0;
}

//程序项目关闭
int project_destroy()
{
    int ret;
    //关闭LCD文件
    ret = close(fd_lcd);
    if(ret == -1)
    {
        perror("Close LCD failed!\n");
        return -1;
    }

    //解除内存映射
    munmap(p_lcd, PIXELS*4);//lcd映射内存

    //关闭触摸屏文件
    ret = close(fd_touch);
    if(ret == -1)
    {
        perror("Close touch screen failed!\n");
        return -1;
    }

    return 0;
}