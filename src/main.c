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

int x, y, ts;
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
        if(touch.type == EV_KEY && touch.code == BTN_TOUCH) // 判断压力值
        {
            if(touch.value == 0)
            {
                if(x < 400)
                {
                    left();
                    show();
                    printf("left\n");
                }
                else
                {
                    if(x > 750 && y > 430)
                    {
                        for(int i=1;i<=3;i++)
                        {
                            left();
                            show();
                        }
                    }
                    else
                    {
                        right();
                        show();
                    }
                    printf("right\n");
                }
            }
        }
    }
    close_EV_ABS();
    close_lcd();
    return 0;
}