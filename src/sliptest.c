// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>//open函数所需要使用的三个头文件
// #include <stdio.h>//标准输入输出的头文件
// #include <unistd.h>//close,read,write函数所需要使用的头文件
// #include <string.h>
// #include <sys/mman.h>//mmap函数所需要使用的头文件
// #include <string.h>
// #include <linux/input.h>
// #include <stdlib.h>  // abs函数所需要使用的头文件


// #define SWIPE_THRESHOLD 50 // 定义滑动的最小距离阈值
// char bmp_name[3][20]={"./1.bmp","./2.bmp","./3.bmp"};

// // int get_xy(int *x, int *y, int *endX, int *endY) // 获取触摸屏坐标
// // {
// //     int startX = 0;
// //     int startY = 0;
// //     struct input_event touch;

// //     int ts = open("/dev/input/event0", O_RDWR);
// //     if (ts < 0) {
// //         perror("open");
// //         return -1;
// //     }

// //     while (1)
// //     {
// //         read(ts, &touch, sizeof(touch));

// //         if (touch.type == EV_ABS && touch.code == ABS_X) // 获取x轴数据
// //         {
// //             *x = touch.value * 800 / 1024; // 把具体数值赋值给x
// //         }
// //         if (touch.type == EV_ABS && touch.code == ABS_Y) // 获取y轴数据
// //         {
// //             *y = touch.value * 480 / 600; // 把具体数值赋值给y
// //         }
// //         if (touch.type == EV_KEY && touch.code == BTN_TOUCH) // 判断压力值
// //         {
// //             if (touch.value == 1) // 当压力值为1时，其实就是按下的时候
// //             {
// //                 startX = *x;
// //                 startY = *y;
// //             }
// //             if (touch.value == 0) // 当压力值为0时，其实就是松手的时候
// //             {
// //                 *endX = *x;
// //                 *endY = *y;
// //                 printf("startX=%d, startY=%d, endX=%d, endY=%d\n", startX, startY, *endX, *endY);

// //                 int deltaX = *endX - startX;
// //                 int deltaY = *endY - startY;

// //                 if (abs(deltaX) > abs(deltaY) && abs(deltaX) > SWIPE_THRESHOLD) // 判断滑动方向
// //                 {
// //                     close(ts);
// //                     if (deltaX < 0)
// //                     {
// //                         printf("左滑\n");
// //                         return -1;
// //                     }
// //                     else
// //                     {
// //                         printf("右滑\n");
// //                         return 1;
// //                     }
// //                 }
// //             }
// //         }
// //     }
// //     close(ts);
// //     return 0;
// // }

// int init_lcd()//初始化LCD
// {
//     // 显示图片的步骤
// // 1.打开LCD文件
//     lcd_fd = open("/dev/fb0", O_RDWR);
//     if(lcd_fd == -1)
//     {
//         perror("open lcd failed");
//         return -1;
//     }
// }


// int show_bmp(char *bmp_name)
// {

// // 2.打开图片文件
//     int bmp_fd = open(bmp_name, O_RDWR);
//     if(bmp_fd == -1)
//     {
//         perror("open bmp failed");
//         return -1;
//     }
// // 3.内存映射
//     int *lcd_p = mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
// // 4.读图片文件54字节
//     char head[54];
//     read(bmp_fd, head, 54);
//     lseek(bmp_fd, 54, SEEK_SET);//跳过格式头的54字节
// // 5.读图片文件800*480*3字节
//     char buf1[800*480*3];
//     read(bmp_fd, buf1, 800*480*3);
// // 6.将读取出来的RGB数据转化成ARGB数据
//     int buf2[800*480];
//     for(int i=0; i<800*480; i++)
//     {
//         buf2[i] = buf1[3*i]<<0 | buf1[3*i+1]<<8 | buf1[3*i+2]<<16 | 0x00<<24;
//     }
// // 7.将ARGB数据写入开发板// 7.将数据颠倒
//     for(int y=0; y<480; y++)
//     {
//         for(int x=0; x<800; x++)
//         {
//             *(lcd_p + x + (479-y)*800) = buf2[x+y*800];
//         }
//     }
// // 8.关闭图片文件
//     close(bmp_fd);
// // 9.解除内存映射
//     munmap(lcd_p, 800*480*4);

    
// }

// int close_lcd()
// {
//     // 10.关闭LCD文件
//     close(lcd_fd);
// }


// int main() {

//     // int x = 0, y = 0, endX = 0, endY = 0;
//     init_lcd();//初始化lcd屏幕设备
//     show_bmp("./1.bmp");//显示图片
//     // int num=0;
//     // show_bmp(bmp_name[num]);//显示图片
//     // while (1) {
//     //     int state = get_xy(&x, &y, &endX, &endY); // 获取触摸屏坐标, 更新xy
//     //     if (state == -1) {
//     //         printf("显示前一个图片\n");
//     //         num--;
//     //     } else if (state == 1) {
//     //         printf("显示后一个图片\n");
//     //         num++;
//     //     }
//     //     if(num>2)num=0;
//     //     if(num<0)num=2;

//     //     show_bmp(bmp_name[num]);//显示图片
//     // }

//    close_lcd();//关闭lcd屏幕设备
//    return 0;
// }
