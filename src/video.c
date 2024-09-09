#include "main.h"

void send_cmd(int fd_fifo, const char * cmd)
{
    int ret_val = write(fd_fifo, cmd, strlen(cmd));
    if(ret_val == -1) perror("指令发送失败....\n");
    printf("success%d\n", ret_val);
}

//视频播放
/*
    输入：视频文件路径
    输出：视频播放
    返回：成功返回0，失败返回-1
*/
void VideoPlay()
{
    //打开视频文件
    system("killall -9 mplayer");
    //操作视频
    VideoMode = 0;
    char Video[255];
    sprintf(Video, "mplayer %s -quiet -slave -input file=/tmp/myFifo -zoom -x 800 -y 480 &", video_path[video_num]);
    FILE * fp = popen(Video, "r");
    sleep(1);
    system("killall -19 mplayer");// 停止播放
    do{
        int nTouch = project_touch(&posx, &posy);
        
        if(nTouch == 0)
        {
            if(posx < 100 && posy < 100) // 退出视频播放器
            {
                mode = 0;
                video_num = 0;
                system("killall -9 mplayer");// 结束播放器
                VideoMode = 0;
                show_1152000bmp("./picture/menu.bmp", p_lcd);//显示菜单
                break;
            }
            else if(posx > 320 && posx < 480 && posy > 160 && posy < 320) // 暂停或继续
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
            else if(posx < 400) // 打开上一个视频
            {
                system("killall -9 mplayer");// 结束播放器
                VideoMode = 0;
                video_num -= 1;
                if(video_num < 0) video_num += VIDEO_CNT;
                sprintf(Video, "mplayer %s -quiet -slave -input file=/tmp/myFifo -zoom -x 800 -y 480 &", video_path[video_num]);
                fp = popen(Video, "r");
                sleep(1);
                system("killall -19 mplayer");// 停止播放
            }
            else // 打开下一个视频
            {
                system("killall -9 mplayer");// 结束播放器
                VideoMode = 0;
                video_num += 1;
                if(video_num >= VIDEO_CNT) video_num -= VIDEO_CNT;
                sprintf(Video, "mplayer %s -quiet -slave -input file=/tmp/myFifo -zoom -x 800 -y 480 &", video_path[video_num]);
                fp = popen(Video, "r");
                sleep(1);
                system("killall -19 mplayer");// 停止播放
            }
        }
        if(nTouch == 1) send_cmd(fd_fifo, "seek +10\n"); // 快进
        if(nTouch == 2) send_cmd(fd_fifo, "seek -10\n"); // 快退
        if(nTouch == 3) send_cmd(fd_fifo, "volume -20\n"); // 减小音量
        if(nTouch == 4) send_cmd(fd_fifo, "volume +20\n"); // 增大音量
    }while(1);
}