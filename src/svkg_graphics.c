#include <glad/glad.h>

#include <GL/gl.h>
#include <slog.h>
#include <stdint.h>
#include <svkg_graphics.h>

SVKG_GraphicsSystem SVKG_GraphicsSystem_Init(int window_w, int window_h,
                                             const char *title) {
    SVKG_GraphicsSystem system = {0};

    if (!glfwInit()) {
        slog_fatal("Failed to initialize GLFW");
        return system;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    system.window = glfwCreateWindow(window_w, window_h, title, NULL, NULL);

    if (!system.window) {
        slog_fatal("Failed to create a window");
        glfwTerminate();
        return (SVKG_GraphicsSystem){0};
    }

    glfwMakeContextCurrent(system.window);

    int version = gladLoadGL();
    if (version == 0) {
        slog_fatal("Failed to load OpenGL");
        return (SVKG_GraphicsSystem){0};
    }
    slog_info("Initialized the GLFW context and the graphics system");
    return system;
}
void SVKG_GraphicsSystem_Destroy(SVKG_GraphicsSystem *system) {
    glfwTerminate();
    system->window = NULL;
}
void SVKG_GraphicsSystem_ClearScreen(SVKG_Color c) {
    glClearColor(c.r / 255.0, c.g / 255.0, c.b / 255.0, c.a / 255.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
SVKG_Color SVKG_Color_Get(uint32_t hex) {
    uint8_t r = (uint8_t)(hex >> 24);
    uint8_t g = (uint8_t)(hex >> 16);
    uint8_t b = (uint8_t)(hex >> 8);
    uint8_t a = (uint8_t)hex;
    return (SVKG_Color){r, g, b, a};
}
