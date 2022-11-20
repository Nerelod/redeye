#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

#define MAXDISPLAYNAME 60
const int START_WIDTH = 32;
const int  START_HEIGHT = 32;

void runWindow(Display *display);
