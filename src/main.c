#include "main.h"

int mode = 0;
int MusicMode = 0;
int VideoMode = 0;
int picture_num = 0;
int music_num = 0;
int video_num = 0;
char* picture_path[PICTURE_CNT] = {"picture/1.bmp", "picture/2.bmp", "picture/3.bmp", "picture/4.bmp", "picture/5.bmp"};
char* music_path[MUSIC_CNT] = {"music/1.mp3", "music/2.mp3", "music/3.mp3"};
char* video_path[VIDEO_CNT] = {"video/1.mp4", "video/2.mp4", "video/3.mp4"};
int main()
{
    //1.程序初始化
    project_init();
    
    //2.为手势识别创建线程
    pthread_create(&hand_tid, NULL, hand, NULL);

    //3.程序主界面
    project_ui();

    //4.程序销毁
    project_destroy();

    return 0;
}
