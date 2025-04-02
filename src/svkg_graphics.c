#include <glad/glad.h>
#include <slog.h>
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
