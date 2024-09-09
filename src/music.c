#include "main.h"

//音乐播放
/*
    #输入：音乐文件路径
    #输出：音乐播放
    #返回：成功返回0，失败返回-1
*/
void MusicPlay()
{
    show_1152000bmp("./picture/music_stop.bmp", p_lcd);
    // //打开音乐文件
    // system("killall -9 mplayer");
    int choice;
    MusicMode = 0;
    char Music[255];
    sprintf(Music, "mplayer %s -quiet -slave -input file=/tmp/myFifo &", music_path[music_num]);
    system(Music);
    system("killall -19 mplayer");// 停止播放
    do{
        int nTouch = project_touch(&posx, &posy);
        
        if(nTouch == 0) // 单击
        {
            printf("music : posx = %d, posy = %d\n", posx, posy);
            if(posx > 27 && posx < 212 && posy > 11 && posy < 63) choice = 0;
            else if(posx > 305 && posx < 514 && posy > 143 && posy < 307) choice = 1;
            else if(posx > 49 && posx < 213 && posy > 167 && posy < 266) choice = 4;
            else if(posx > 592 && posx < 756 && posy > 173 && posy < 256) choice = 5;
            else if(posx > 106 && posx < 292 && posy > 360 && posy < 416) choice = 3;
            else if(posx > 524 && posx < 700 && posy > 361 && posy < 419) choice = 2;

            switch(choice)
            {
                case 0:
                    mode = 0;
                    music_num = 0;
                    printf("music : posx = %d, posy = %d\n", posx, posy);
                    printf("Exit\n");
                    system("killall -9 mplayer");// 结束播放器
                    show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
                    break;
                case 1:
                    if(MusicMode == 1)
                    {
                        printf("music : posx = %d, posy = %d\n", posx, posy);
                        printf("stop\n");
                        system("killall -19 mplayer");// 停止播放
                        MusicMode = 0;
                        show_1152000bmp("./picture/music_stop.bmp", p_lcd);
                    }
                    else
                    {
                        printf("music : posx = %d, posy = %d\n", posx, posy);
                        printf("continue\n");
                        system("killall -18 mplayer");// 继续播放
                        MusicMode = 1;
                        show_1152000bmp("./picture/music.bmp", p_lcd);
                    }
                    break;
                case 2:
                    printf("music : posx = %d, posy = %d\n", posx, posy);
                    printf("volume-\n");
                    send_cmd(fd_fifo, "volume -20\n");
                    break;
                case 3:
                    printf("music : posx = %d, posy = %d\n", posx, posy);
                    printf("volume+\n");
                    send_cmd(fd_fifo, "volume +20\n");
                    break;
                case 4:
                    printf("music : posx = %d, posy = %d\n", posx, posy);
                    printf("seek\n");
                    send_cmd(fd_fifo, "seek -10\n");
                    break;
                case 5:
                    printf("music : posx = %d, posy = %d\n", posx, posy);
                    printf("seek\n");
                    send_cmd(fd_fifo, "seek +10\n");
                    break;
                default:
                    printf("music : posx = %d, posy = %d\n", posx, posy);
                    printf("Error!\n");
                    break;
            }
        }
        if(nTouch == 1) // 向右划
        {
            system("killall -9 mplayer");// 结束播放器
            MusicMode = 0;
            music_num -= 1;
            if(music_num < 0) music_num += MUSIC_CNT;
            show_1152000bmp("./picture/music_stop.bmp", p_lcd);
            sprintf(Music, "mplayer %s -quiet -slave -input file=/tmp/myFifo &", music_path[music_num]);
            system(Music);
            system("killall -19 mplayer");// 停止播放
        }
        if(nTouch == 2) // 向左划
        {
            system("killall -9 mplayer");// 结束播放器
            MusicMode = 0;
            music_num += 1;
            if(music_num >= MUSIC_CNT) music_num -= MUSIC_CNT;
            show_1152000bmp("./picture/music_stop.bmp", p_lcd);
            sprintf(Music, "mplayer %s -quiet -slave -input file=/tmp/myFifo &", music_path[music_num]);
            system(Music);
            system("killall -19 mplayer");// 停止播放
        }
        if(nTouch == 3) // 向下划
        {
            send_cmd(fd_fifo, "volume -20\n");
        }
        if(nTouch == 4) // 向上划
        {
            send_cmd(fd_fifo, "volume +20\n");
            continue;

            // 退出音频播放器
            mode = 0;
            music_num = 0;
            system("killall -9 mplayer");// 结束播放器
            MusicMode = 0;
            show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
            break;
        }
    }while(choice != 0);
}
