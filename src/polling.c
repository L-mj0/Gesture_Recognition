#include "main.h"

//幻灯片
/*
    #输入：延时时间，单位秒
    #输出：幻灯片播放
    #返回：成功返回0，失败返回-1
*/
void Polling()
{
    show_1152000bmp(picture_path[picture_num], p_lcd);
    do{
        //换图
        int nTouch = project_touch(&posx, &posy);
        if((nTouch == 0 && posx > 400) || nTouch == 2)//点击到了右边或左划
        {
            picture_num += 1;
            if(picture_num >= PICTURE_CNT) picture_num -= PICTURE_CNT;
            show_1152000bmp(picture_path[picture_num], p_lcd);
        }
        else if((nTouch == 0 && posx < 400) || nTouch == 1)//点击到了左边或右划
        {
            picture_num -= 1;
            if(picture_num < 0) picture_num += PICTURE_CNT;
            show_1152000bmp(picture_path[picture_num], p_lcd);
        }
        else if(nTouch == 4)//上划
        {
            mode = 0;
            picture_num = 0;
            printf("Exit!\n");
            show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
            break;
        }
    }while(1);
}
