#ifndef _MAIN_H_
#define _MAIN_H_

/*头文件*/
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <linux/input.h>
#include <pthread.h>

#include "show_bmp.h"

/*全局变量*/
int mode;// 当前模式（初始菜单，图片展示，音频播放，视频播放，玩法介绍）
int fd_lcd;//LCD文件
int fd_touch;//touch文件
int* p_lcd;//LCD映射内存
int posx, posy;//存放坐标
int fd_fifo;//用于发送指令的管道文件
pthread_t hand_tid;// 线程的tid（线程号）
int MusicMode;// 音频播放状态
int VideoMode;// 视频播放状态
int picture_num;// 当前展示哪一张图片
int music_num;// 当前播放哪一段音频
int video_num;// 当前播放哪一段视频
char* picture_path[5];// 图片路径
char* music_path[3];// 音频路径
char* video_path[3];// 视频路径
/*结构体定义*/
struct input_event touch;//触摸屏结构体

/*宏定义*/
#define PICTURE_CNT 5// 图片个数
#define MUSIC_CNT 3// 音频个数
#define VIDEO_CNT 3// 视频个数
#define PIXELS 800*480//屏幕像素点
#define FIFO_PATH "/tmp/myFifo" // 管道文件目录

/*联合体*/

/*枚举*/

/*函数声明*/
int project_init(void);//程序初始化
int project_ui(void);//程序主界面
int project_destroy(void);//程序销毁
int project_touch(int*, int*);//触摸屏操作函数
void *hand(void *arg);// 手势识别函数

void send_cmd(int fd_fifo, const char * cmd);//写入管道文件

void Polling();
void MusicPlay();
void VideoPlay();
void Introduction();
#endif