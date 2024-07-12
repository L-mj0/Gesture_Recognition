#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "touch.h"

int ts;
struct input_event touch;
int init_EV_ABS()
{
    int ts = open("/dev/input/event0", O_RDWR);
    return ts;
}
void close_EV_ABS()
{
    close(ts);
}