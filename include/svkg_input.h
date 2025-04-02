#ifndef SVKG_INPUT_H
#define SVKG_INPUT_H
#include <stdbool.h>
#include <GLFW/glfw3.h>

typedef struct {
    bool keys[GLFW_KEY_LAST + 1];
    bool prev_keys[GLFW_KEY_LAST + 1];
    bool mouse_buttons[GLFW_MOUSE_BUTTON_LAST + 1];
    bool prev_mouse_buttons[GLFW_MOUSE_BUTTON_LAST + 1];
    double mouse_x, mouse_y;
    double scroll_dy;
    double next_scroll_dy;
} SVKG_InputSystem;

SVKG_InputSystem SVKG_InputSystem_Init();
void SVKG_InputSystem_Update(SVKG_InputSystem* sys);

#endif
