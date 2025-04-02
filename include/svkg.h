#ifndef SVKG_H
#define SVKG_H

#include "svkg_audio.h"
#include "svkg_input.h"
#include "svkg_math.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct {
    GLFWwindow* window;
    SVKG_InputSystem input;
    SVKG_AudioSystem audio;
} SVKG_Context;

SVKG_Context *SVKG_ContextInit(int window_w, int window_h, const char *title);
void SVKG_ContextDestroy(SVKG_Context* ctx);
bool SVKG_ContextShouldQuit(const SVKG_Context* ctx);

void SVKG_ContextBeginFrame(SVKG_Context* ctx);
void SVKG_ContextEndFrame(SVKG_Context* ctx);

bool SVKG_Input_IsKeyPressed(const SVKG_Context *ctx, int key); 
bool SVKG_Input_IsKeyJustPressed(const SVKG_Context *ctx, int key); 

bool SVKG_Input_IsMouseButtonPressed(const SVKG_Context *ctx, int button); 
bool SVKG_Input_IsMouseButtonJustPressed(const SVKG_Context *ctx, int button); 
SVKG_Vec2 SVKG_Input_GetMousePosition(const SVKG_Context *ctx); 
float SVKG_Input_GetMousePositionX(const SVKG_Context *ctx); 
float SVKG_Input_GetMousePositionY(const SVKG_Context *ctx); 
float SVKG_Input_GetScrollDelta(const SVKG_Context *ctx); 


#endif
