#ifndef RESIZE_HANDLE
#define RESIZE_HANDLE
struct ResizeHandler {
	int lastWindowWidth = 0;
	int lastWindowHeight = 0;

	int windowWidth = 0;
	int windowHeight = 0;

	bool shouldResize = false;
};
extern struct ResizeHandler Resize;
#endif