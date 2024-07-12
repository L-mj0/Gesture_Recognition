#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "show_bmp.h"
#include "touch.h"
#include <stdlib.h>

// #define SWIPE_THRESHOLD 50 // 定义滑动的最小距离阈值

int x, y, ts,startX, endX, startY, endY;; 
int val = 0;
struct input_event touch;
void left()
{
    val = val + 1;
    // val = val + 3 - 1;
    val %= 3;
}
void right()
{
    val = val + 3 - 1;
    // val = val + 1;
    val %= 3;
}
void show()
{
    if(val == 0) show_bmp("1.bmp");
    if(val == 1) show_bmp("2.bmp");
    if(val == 2) show_bmp("3.bmp");
    sleep(1);
}

int main()
{
    
    init_lcd();
    ts = init_EV_ABS();
    show();
    while(1)
    {
        read(ts, &touch, sizeof(touch));
        if(touch.type == EV_ABS && touch.code == ABS_X) x = touch.value * 800 / 1024;
        if(touch.type == EV_ABS && touch.code == ABS_Y) y = touch.value * 480 / 600;
        if (touch.type == EV_KEY && touch.code == BTN_TOUCH) // 判断压力值
        {
            if (touch.value == 1) // 当压力值为1时，其实就是按下的时候
            {
                startX = x;
                startY = y;
            }
            if (touch.value == 0) // 当压力值为0时，其实就是松手的时候
            {
                endX = x;
                endY = y;
                printf("startX=%d, startY=%d, endX=%d, endY=%d\n", startX, startY, endX, endY);

                int deltaX = endX - startX;
                int deltaY = endY - startY;

                if (abs(deltaX) > abs(deltaY) && abs(deltaX) > SWIPE_THRESHOLD) // 判断滑动方向
                {
                    if (deltaX < 0)
                    {
                        printf("左滑\n");
                        left();
                    }
                    else
                    {
                        printf("右滑\n");
                        right();
                    }
                    show();
                }
            }
        }

    }
    close_EV_ABS();
    close_lcd();
    return 0;
}