#include "main.h"

void Introduction()
{
    char* bmpname = "./picture/introduction.bmp";
    pic_circular_shrink(bmpname, p_lcd);
    
    while(1)
    {
        int nTouch = project_touch(&posx, &posy);

        if(nTouch == 4) //上划
        {
            mode = 0;
            break;
        }
    }
}