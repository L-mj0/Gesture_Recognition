#include "main.h"

void *hand(void *arg)
{
    char hand_data;
    char Music[255];
    char Video[255];
    int hand_fd = open("/dev/IIC_drv", O_RDWR);// 打开手势识别模块
    if(hand_fd == -1) perror("open IIC_drv");
    while(1)
    {
        read(hand_fd, &hand_data, 1);
        // printf("hand_data = %d\n", (int)hand_data);
        if(hand_data == 1)
        {
            if(mode == 1) send_cmd(fd_fifo, "volume +20\n"); // 增大音量
            if(mode == 2) // 退回主菜单
            {
                mode = 0;
                picture_num = 0;
                printf("Exit!\n");
                show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
            }
            if(mode == 3) send_cmd(fd_fifo, "volume +20\n"); // 增大音量
            if(mode == 4) // 退回主菜单
            {
                mode = 0;
                printf("Exit!\n");
                show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
            }
            printf("up!\n");
            //printf("向上手势!\n");
        }
        if(hand_data == 2)
        {
            if(mode == 1) send_cmd(fd_fifo, "volume -20\n"); // 减小音量
            if(mode == 3) send_cmd(fd_fifo, "volume -20\n"); // 减小音量
            printf("down!\n");
            //printf("向下手势!\n");
        }
        if(hand_data == 3)
        {
            if(mode == 1)
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
            if(mode == 2)
            {
                picture_num -= 1;
                if(picture_num < 0) picture_num += PICTURE_CNT;
                show_1152000bmp(picture_path[picture_num], p_lcd);
            }
            if(mode == 3)
            {
                system("killall -9 mplayer");// 结束播放器
                VideoMode = 0;
                video_num -= 1;
                if(video_num < 0) video_num += VIDEO_CNT;
                sprintf(Video, "mplayer %s -quiet -slave -input file=/tmp/myFifo -zoom -x 800 -y 480 &", video_path[video_num]);
                FILE * fp = popen(Video, "r");
                sleep(1);
                system("killall -19 mplayer");// 停止播放
            }
            printf("left!\n");
            //printf("向左手势!\n");
        }
        if(hand_data == 4)
        {
            if(mode == 1)
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
            if(mode == 2)
            {
                picture_num += 1;
                if(picture_num >= PICTURE_CNT) picture_num -= PICTURE_CNT;
                show_1152000bmp(picture_path[picture_num], p_lcd);
            }
            if(mode == 3)
            {
                system("killall -9 mplayer");// 结束播放器
                VideoMode = 0;
                video_num += 1;
                if(video_num >= VIDEO_CNT) video_num -= VIDEO_CNT;
                sprintf(Video, "mplayer %s -quiet -slave -input file=/tmp/myFifo -zoom -x 800 -y 480 &", video_path[video_num]);
                FILE * fp = popen(Video, "r");
                sleep(1);
                system("killall -19 mplayer");// 停止播放
            }
            printf("right!\n");
            //printf("向右手势!\n");
        }
        if(hand_data == 5)
        {
            if(mode == 1)
            {
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
            }
            if(mode == 3)
            {
                if(VideoMode == 0)
                {
                    VideoMode = 1;
                    system("killall -18 mplayer");// 继续播放
                }
                else if(VideoMode == 1)
                {
                    VideoMode = 0;
                    system("killall -19 mplayer");// 停止播放
                }
            }
            //printf("向前手势!\n");
        }
        if(hand_data == 6)
        {
            printf("向后手势!\n");
        }
        if(hand_data == 7)
        {
            if(mode == 1) send_cmd(fd_fifo, "seek +10\n"); // 快进
            if(mode == 3) send_cmd(fd_fifo, "seek +10\n"); // 快进
            printf("顺时针手势!\n");
        }
        if(hand_data == 8)
        {
            if(mode == 1) send_cmd(fd_fifo, "seek -10\n"); // 快退
            if(mode == 3) send_cmd(fd_fifo, "seek -10\n"); // 快退
            printf("逆时针手势!\n");
        }
        if(hand_data == 9)
        {
            if(mode == 1)
            {
                mode = 0;
                music_num = 0;
                system("killall -9 mplayer");// 结束播放器
                MusicMode = 0;
                show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
            }
            if(mode == 2)
            {
                mode = 0;
                picture_num = 0;
                printf("Exit!\n");
                show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
            }
            if(mode == 3)
            {
                mode = 0;
                video_num = 0;
                system("killall -9 mplayer");// 结束播放器
                VideoMode = 0;
                show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
            }
            if(mode == 4)
            {
                mode = 0;
                printf("Exit!\n");
                show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
            }
            // printf("摇摆手势!\n");
        }
        if(hand_data == -1)
        {
            printf("无手势!\n");
        }
    }
    close(hand_fd);
}