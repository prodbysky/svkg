#ifndef SVKG_GRAPHICS_H
#define SVKG_GRAPHICS_H
#include "GLFW/glfw3.h"
typedef struct {
    GLFWwindow* window;
} SVKG_GraphicsSystem;

SVKG_GraphicsSystem SVKG_GraphicsSystem_Init(int window_w, int window_h, const char* title);
void SVKG_GraphicsSystem_Destroy(SVKG_GraphicsSystem *system);

#endif
