#include "show_bmp.h"
#include"main.h"

/*
	功能：显示800*480大小的bmp图片。
	参数：
		char *pathname：要显示图片的名字。
		int *show_1152000bmp_fd：被映射区的指针。
	返回值：成功  0
			失败  -1
*/
int show_1152000bmp(char *pathname, int *show_1152000bmp_fd)
{
	//1、打开BMP格式图片和lcd显示屏
	int fd_bmp = open(pathname,  O_RDWR);
	if(fd_bmp == -1)
	{
		perror("show_1152000bmp(), open bmp fail!\n");
		return -1;
	}
	
	//2、去掉54个字节
	int ret = lseek(fd_bmp, 54, SEEK_SET);
	if(ret == -1)
	{
		printf("show_1152000bmp(), lseek bmp fail!\n");
		return -1;		
	}
	
	//3、读取BMP数据到lcd屏幕中
	char bmp_buf[800*480*3];
	int lcd_buf[800*480];
	bzero(bmp_buf, 800*480*3);
	bzero(lcd_buf, 800*480);
	
	ret = read(fd_bmp, bmp_buf, 800*480*3);//BMP数据放到了bmp_buf中
	if(ret == -1)
	{
		printf("show_1152000bmp(), read bmp fail!\n");
		return -1;		
	}		

	//4、关闭文件，回收资源
	close(fd_bmp);
	
	//5、800*480个A像素变成800*480个B像素算法。
	int i;
	for(i=0; i<800*480; i++)
	{
		lcd_buf[i] = bmp_buf[i*3]<<0 | bmp_buf[i*3+1]<<8 | bmp_buf[i*3+2]<<16;
		//lcd_buf[0] = bmp_buf[0]<<0 | bmp_buf[1]<<8 | bmp_buf[2]<<16;
		//lcd_buf[1] = bmp_buf[3]<<0 | bmp_buf[4]<<8 | bmp_buf[5]<<16;
		//lcd_buf[2] = bmp_buf[6]<<0 | bmp_buf[7]<<8 | bmp_buf[8]<<16;
	}
	
	//6、lcd_buf数据（DDR2中的数据）通过mmap显示到LCD屏幕中。
/*
	for(i=0; i<800*480; i++)
	{
		*(lcd_mmap+i)=lcd_buf[i];
	}	
*/
	int x, y;
	for(y=0; y<480; y++)//优化算法，解决图片颠倒问题
	{
		for(x=0; x<800; x++)
		{
			*(show_1152000bmp_fd+800*(479-y)+x)= lcd_buf[800*y+x];
		}
	}
			
	return 0;
}

/*
	功能：切换BMP图片特效”圆形收缩“。
	参数：	
		char *pathname：图片的路径。
		int *pic_circular_shrink_fd：被映射区的指针。
	返回值：成功  0
			失败  -1		
*/
int pic_circular_shrink(char *pathname, int* pic_circular_shrink_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
	if(bmp_fd == -1)
	{
		printf("pic_circular_shrink(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
	if(ret == -1)
	{
		perror("pic_circular_shrink(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
	if(ret == -1)
	{
		printf("pic_circular_shrink(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5、关闭图片

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6、24bits 转 32bits控制变量
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7、解决图片上下颠倒问题
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	//8、特殊动画“圆形收缩”效果算法
	for(k=468; k>=0; k-=3)
	{
		for(i=0; i<480; i++)
		{
			for(j=0; j<800; j++)
			{
				if((j-400)*(j-400)+(i-240)*(i-240) >= k*k)
					pic_circular_shrink_fd[800*i+j] = mi_buf[800*i+j];
			}
		}
	}	
		
	return 0;
}