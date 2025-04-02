#include <glad/glad.h>
#include <string.h>

#include "GLFW/glfw3.h"
#include "svkg_audio.h"
#include "svkg_input.h"
#include "svkg_math.h"
#include <slog.h>
#include <stdlib.h>
#include <svkg.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);
static void cursor_callback(GLFWwindow *window, double xpos, double ypos);
static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int mods);
static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

SVKG_Context *SVKG_ContextInit(int window_w, int window_h, const char *title) {
  SVKG_Context *ctx = calloc(1, sizeof(SVKG_Context));
  ctx->input = SVKG_InputSystem_Init();

  slog_init("svkg_log", SLOG_FLAGS_ALL, 1);
  slog_config_t cfg;
  slog_config_get(&cfg);
  cfg.nToFile = 0;
  cfg.nToScreen = 1;
  slog_config_set(&cfg);

  if (!glfwInit()) {
    slog_fatal("Failed to initialize GLFW");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  ctx->window = glfwCreateWindow(window_w, window_h, title, NULL, NULL);

  if (!ctx->window) {
    slog_fatal("Failed to create a window");
    glfwTerminate();
    return NULL;
  }
  glfwSetWindowUserPointer(ctx->window, ctx);
  glfwSetKeyCallback(ctx->window, key_callback);
  glfwSetCursorPosCallback(ctx->window, cursor_callback);
  glfwSetMouseButtonCallback(ctx->window, mouse_button_callback);
  glfwSetScrollCallback(ctx->window, scroll_callback);

  glfwMakeContextCurrent(ctx->window);

  int version = gladLoadGL();
  if (version == 0) {
    slog_fatal("Failed to load OpenGL");
    return NULL;
  }

  ctx->audio = SVKG_AudioSystem_Init();

  slog_info("Successfully loaded and initialized the SVKG context");
  return ctx;
}

void SVKG_ContextDestroy(SVKG_Context *ctx) {
  glfwTerminate();
  slog_destroy();
  ctx->window = NULL;
  SVKG_AudioSystem_Destroy(&ctx->audio);
  free(ctx);
}

bool SVKG_ContextShouldQuit(const SVKG_Context *ctx) {
  return glfwWindowShouldClose(ctx->window);
}

void SVKG_ContextBeginFrame(SVKG_Context *ctx) {
  SVKG_InputSystem_Update(&ctx->input);
}
void SVKG_ContextEndFrame(SVKG_Context *ctx) {
  glfwSwapBuffers(ctx->window);
  glfwPollEvents();
}

bool SVKG_Input_IsKeyPressed(const SVKG_Context *ctx, int key) {
  if (key < 0 || key > GLFW_KEY_LAST) {
    return false;
  }
  return ctx->input.keys[key];
}
bool SVKG_Input_IsKeyJustPressed(const SVKG_Context *ctx, int key) {
  if (key < 0 || key > GLFW_KEY_LAST) {
    return false;
  }
  return ctx->input.keys[key] && !ctx->input.prev_keys[key];
}

bool SVKG_Input_IsMouseButtonPressed(const SVKG_Context *ctx, int button) {
  if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) {
    return false;
  }
  return ctx->input.mouse_buttons[button];
}
bool SVKG_Input_IsMouseButtonJustPressed(const SVKG_Context *ctx, int button) {
  if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) {
    return false;
  }
  return ctx->input.mouse_buttons[button] &&
         !ctx->input.prev_mouse_buttons[button];
}
float SVKG_Input_GetMousePositionX(const SVKG_Context *ctx) {
  return ctx->input.mouse_x;
}
float SVKG_Input_GetMousePositionY(const SVKG_Context *ctx) {
  return ctx->input.mouse_y;
}

SVKG_Vec2 SVKG_Input_GetMousePosition(const SVKG_Context *ctx) {
  return (SVKG_Vec2){
      .x = ctx->input.mouse_x,
      .y = ctx->input.mouse_y,
  };
}
float SVKG_Input_GetScrollDelta(const SVKG_Context *ctx) {
  return ctx->input.scroll_dy;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  (void)scancode;
  (void)mods;
  SVKG_Context *ctx = glfwGetWindowUserPointer(window);
  if (key >= 0 && key <= GLFW_KEY_LAST) {
    ctx->input.keys[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);
  }
}

static void cursor_callback(GLFWwindow *window, double xpos, double ypos) {
  SVKG_Context *ctx = glfwGetWindowUserPointer(window);
  ctx->input.mouse_x = xpos;
  ctx->input.mouse_y = ypos;
}

static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int mods) {
  (void)mods;
  SVKG_Context *ctx = glfwGetWindowUserPointer(window);
  if (button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST) {
    ctx->input.mouse_buttons[button] = (action == GLFW_PRESS);
  }
}

static void scroll_callback(GLFWwindow *window, double xoffset,
                            double yoffset) {
  (void)xoffset;
  SVKG_Context *ctx = glfwGetWindowUserPointer(window);
  ctx->input.next_scroll_dy += yoffset;
}
