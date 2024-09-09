#include "main.h"

int project_touch(int *th_x, int *th_y)
{
    //获取坐标
/*
	输入：屏幕点击
	输出：点击的坐标(th_x, th_y)
	返回：异常-1,点击0，向右移动1，向左移动2,向下移动3,向上移动4
	注意：需要两个int指针存放坐标
*/
    int touch_val = -1;
    int old_x, old_y, new_x, new_y;
    int touch_fd = open("/dev/input/event0", O_RDWR);
    struct input_event touch;

    old_x = old_y = -1;
	while(1)
	{
		read(touch_fd, &touch, sizeof(touch));
        
		//这是开发板驱动问题，开发板的屏幕像素是800*480，但驱动给的分辨率有误，驱动的分辨率是1024*600，所以需要乘相应的值
		//触控驱动正常的开发板无需乘这些值，即使用注释的代码，无需使用源代码
        if(old_x == -1 || old_y == -1)
        {
            if(touch.type == EV_ABS && touch.code == ABS_X) old_x = touch.value * 800 / 1024;
            if(touch.type == EV_ABS && touch.code == ABS_Y) old_y = touch.value * 480 / 600;
            *th_x = old_x;
            *th_y = old_y;
            sleep(0.2);
        }
		else
        {
            if(touch.type == EV_ABS && touch.code == ABS_X) *th_x = touch.value * 800 / 1024;
            if(touch.type == EV_ABS && touch.code == ABS_Y) *th_y = touch.value * 480 / 600;
        }

		if (touch.type == EV_KEY && touch.code == BTN_TOUCH && touch.value == 0)
		{
            int dx, dy;
            dx = *th_x - old_x;
            dy = *th_y - old_y;
            if (dx < 0) dx = -dx;
            if (dy < 0) dy = -dy;
            if (dx <= 50 && dy <= 50) touch_val = 0;// 单击
            else if (dx > dy) // 左、右
            {
                if (old_x < *th_x) touch_val = 1;//向右移动
                else touch_val = 2;//向左移动
            }
            else // 上、下
            {
                if (old_y < *th_y) touch_val = 3;//向下移动
                else touch_val = 4;//向上移动
            }
            old_x = old_y = -1;
			break;
		}
	}
    close(touch_fd);
	return touch_val;
}