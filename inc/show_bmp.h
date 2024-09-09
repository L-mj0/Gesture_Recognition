
#ifndef __SHOW_BMP_H__
#define __SHOW_BMP_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <strings.h>

/*
	功能：显示800*480大小的bmp图片。
	参数：
		char *pathname：要显示图片的名字。
		int *show_1152000bmp_fd：被映射区的指针。
	返回值：成功  0
			失败  -1
*/
int show_1152000bmp(char *pathname, int *show_1152000bmp_fd);


/*
	功能：切换BMP图片特效”圆形收缩“。
	参数：	
		char *pathname：图片的路径。
		int *pic_circular_shrink_fd：被映射区的指针。
	返回值：成功  0
			失败  -1		
*/
int pic_circular_shrink(char *pathname, int* pic_circular_shrink_fd);


#endif