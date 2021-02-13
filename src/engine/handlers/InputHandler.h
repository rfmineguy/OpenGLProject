#ifndef INPUT_HANDLE
#define INPUT_HANDLE
struct InputHandler {
	bool keys[300]{};
	double lastX = 480, lastY = 270;
    double yaw{}, pitch{}, roll{};
    double sensitivity = 0.3;
};
extern struct InputHandler Input;
#endif