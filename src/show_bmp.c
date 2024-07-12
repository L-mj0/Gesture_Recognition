#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include "show_bmp.h"

int lcd_fd;
int* lcd_p;

void init_lcd()
{
    lcd_fd = open("/dev/fb0", O_RDWR);
    if(lcd_fd == -1) perror("open error");

    lcd_p = mmap(NULL, 480*800*4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
}

void show_bmp(char* bmpname)
{
    int bmp_fd = open(bmpname, O_RDWR);
    if(bmp_fd == -1) perror("open error");
    char bmp_front[54] = {0};
    read(bmp_fd, bmp_front, sizeof(bmp_front));
    char bmp_bgr[480][800][3] = {0};
    read(bmp_fd, bmp_bgr, sizeof(bmp_bgr));
    int image[480][800] = {0};
    for(int i=0,I=479;i<480,I>=0;i++,I--)
    for(int j=0;j<800;j++)
    image[I][j] = (bmp_bgr[i][j][0]<<0) | (bmp_bgr[i][j][1]<<8) | (bmp_bgr[i][j][2]<<16);
    for(int i=0;i<480;i++)
    for(int j=0;j<800;j++)
    *(lcd_p+i*800+j) = image[i][j];
    close(bmp_fd);
}

void close_lcd()
{
    munmap(lcd_p, 480*800*4);
    close(lcd_fd);
}