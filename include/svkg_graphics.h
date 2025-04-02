#ifndef SVKG_GRAPHICS_H
#define SVKG_GRAPHICS_H
#include "GLFW/glfw3.h"
#include <stdint.h>

typedef struct {
    GLFWwindow* window;
} SVKG_GraphicsSystem;

SVKG_GraphicsSystem SVKG_GraphicsSystem_Init(int window_w, int window_h, const char* title);
void SVKG_GraphicsSystem_Destroy(SVKG_GraphicsSystem *system);

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} SVKG_Color;

#define SVKG_Color_Black (SVKG_Color){0, 0, 0, 255}
#define SVKG_Color_White (SVKG_Color){255, 255, 255, 255}

SVKG_Color SVKG_Color_Get(uint32_t hex);


#endif
