#include "redeye.h"

Display *display;
Window root;
Window window;
XColor foregroundColor;
XColor backgroundColor;

int screen;
unsigned int depth;
unsigned int windowWidth;
unsigned int windowHeight;

char *background = NULL;

void SetupColors(){
	XColor exactColor;
	Colormap colorMap;
	
	colorMap = DefaultColormap(display, screen);

	background = "red";
	
	XAllocNamedColor(display, colorMap, background, &backgroundColor, &exactColor);
}

void Draw(void){
	XFillRectangle(display, window, DefaultGC(display, screen), 0, 0, windowWidth, windowHeight);
	XFlush(display);
}

int RunScreen(void){
	XEvent event;
	while(XPending(display)){
		XNextEvent(display, &event);
		switch(event.type){
			case Expose:
				break;
			default:
				break;
		}
	}
	return 1;
}

void Process(char *displayName){
	InitScreen(displayName);
	RunScreen();
}

void InitScreen(char *displayName){
	srand(time(NULL));
	XSetWindowAttributes windowAttributes;
	printf("oh yeah");
	unsigned long windowMask;
	Window tempRoot;
	int windowPointX;
	int windowPointY;
	unsigned int borderWidth;
	int event_base, error_base;

	display = XOpenDisplay(displayName);
	screen = DefaultScreen(display);
	depth = DefaultDepth(display, screen);
	root = RootWindow(display, screen);
	XGetGeometry(display, root, &tempRoot, 
				&windowPointX, &windowPointY,
				&windowWidth, &windowHeight,
				&borderWidth, &depth);
	
	SetupColors();
	
	windowAttributes.background_pixel = backgroundColor.pixel;
	windowAttributes.override_redirect = True;
	XChangeWindowAttributes(display, root, 0, &windowAttributes);	
	windowMask = CWBackPixel | CWOverrideRedirect;
	
	int xcord = rand() % windowWidth;
	int ycord = rand() % windowHeight;
	window = XCreateWindow(display, root, xcord, ycord, START_WIDTH, START_HEIGHT,
							0, depth, InputOutput, CopyFromParent, windowMask,
							&windowAttributes);
	XMapWindow(display, window); 
	XSelectInput(display, window, ExposureMask|VisibilityChangeMask|KeyPressMask);
	XFlush(display);
}

int main(int argc, char *argv[]){
	char displayName[MAXDISPLAYNAME];
	while(1){
		sleep(2);
		printf("running");
		Process(displayName);
	}
	return 0;
}
