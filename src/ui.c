#include "main.h"

//菜单选择
/*
    #输入：无
    #输出：显示菜单以及选择的菜单项
    #返回值：选择的菜单项 0~4
*/
int ModeSelect()
{
    show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单

    //获取坐标
    int SlideMode = project_touch(&posx, &posy);
    printf("posx = %d, posy = %d\nSlideMode = %d\n", posx, posy, SlideMode); //test
    
    if(posx > 50 && posx < 360 && posy > 65 && posy < 200) mode = 1;
    else if(posx > 58 && posx < 364 && posy > 268 && posy < 402) mode = 3;
    else if(posx > 424 && posx < 724 && posy > 68 && posy < 206) mode = 2;
    else if(posx > 432 && posx < 738 && posy > 272 && posy < 403) mode = 4;
    else mode = 0;

    return mode;
}

//UI界面
int project_ui()
{
    //1.开机提示
    printf("Welcome to my project!!\n");
    printf("-------------------------\n");
    printf("PICTURE: 1.picture polling\n2.music playing\n3.video playing\n4.introduction\n0.exit\n");
    show_1152000bmp("./picture/hello.bmp", p_lcd);//开机界面
    system("mplayer ./music/begin.mp3 &");
    sleep(3);
    system("killall -9 mplayer");
    sleep(2);
    show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
    system("killall -9 mplayer");//防止复活

    //2.项目功能
    int choice;
    do{
        //提示选择要进行的项目
        choice = ModeSelect();
        printf("Menu load success!\n");
        switch(choice)
        {
            //(0)退出
            case 0:
                system("killall -9 mplayer"); // 防止有音视频正在播放
                show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
                printf("Exit!\n");
                break;
            //(1)音乐播放器
            case 1:
                MusicPlay();
                break;
            //(2)图片播放器
            case 2:
                Polling();
                break;
            //(3)视频播放
            case 3:
                VideoPlay();
                break;
            //(4)玩法说明
            case 4:
				Introduction();
                break;
            //输入错误
            default:
                printf("Wrong!\n");
                break;
        }
    }while(1);

    return 0;
}