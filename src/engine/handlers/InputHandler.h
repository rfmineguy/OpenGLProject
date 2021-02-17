#ifndef INPUT_HANDLE
#define INPUT_HANDLE
struct InputHandler {
	bool keys[360]{};
	double lastX = 480, lastY = 270;
    double yaw{}, pitch{}, roll{};
    double sensitivity = 0.3;
    bool mouseEnabled = true;
    bool keyEnabled = true;
};
extern struct InputHandler Input;
#endif