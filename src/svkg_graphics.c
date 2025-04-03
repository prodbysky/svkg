#include <glad/glad.h>

#include "cglm/cam.h"
#include <GL/gl.h>
#include <slog.h>
#include <stdint.h>
#include <stdlib.h>
#include <svkg_graphics.h>

SVKG_GraphicsSystem SVKG_GraphicsSystem_Init(int window_w, int window_h,
                                             const char *title) {

    const char *vs_source = " \
    #version 330 core \n\
    layout (location = 0) in vec2 aPos; \
    uniform mat4 uProjection; \
    uniform vec2 uOffset; \
    uniform vec2 uSize; \
    void main() { \
        vec2 pos = aPos * uSize + uOffset; \
        gl_Position = uProjection * vec4(pos, 0.0, 1.0); \
    }";

    const char *fs_source = " \
    #version 330 core \n\
    out vec4 FragColor; \
    uniform vec4 uColor; \
    void main() { \
        FragColor = uColor; \
    }";

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

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vs_source, 0);
    glCompileShader(vs);
    {
        GLint success;
        char infoLog[512];
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vs, 512, NULL, infoLog);
            slog_fatal("Vertex shader compilation failed: %s", infoLog);
        }
    }

    glShaderSource(fs, 1, &fs_source, 0);
    glCompileShader(fs);

    {
        GLint success;
        char infoLog[512];
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fs, 512, NULL, infoLog);
            slog_fatal("Fragment shader compilation failed: %s", infoLog);
        }
    }
    glm_ortho(0, window_w, window_h, 0, -1, 1, system.projection);
    system.shader = glCreateProgram();
    glAttachShader(system.shader, vs);
    glAttachShader(system.shader, fs);
    glLinkProgram(system.shader);
    glUseProgram(system.shader);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glUseProgram(system.shader);
    glUniformMatrix4fv(glGetUniformLocation(system.shader, "uProjection"), 1,
                       GL_FALSE, system.projection[0]);

    const float vertices[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                              0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

    glGenVertexArrays(1, &system.vao);
    glGenBuffers(1, &system.vbo);

    glBindVertexArray(system.vao);
    glBindBuffer(GL_ARRAY_BUFFER, system.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

void SVKG_GraphicsSystem_DrawRectangle(SVKG_GraphicsSystem *system, float x,
                                       float y, float w, float h,
                                       SVKG_Color color) {
    glUseProgram(system->shader);

    const float color_arr[] = {color.r / 255.0, color.g / 255.0,
                               color.b / 255.0, color.a / 255.0};

    glUniform2f(glGetUniformLocation(system->shader, "uOffset"), x, y);
    glUniform2f(glGetUniformLocation(system->shader, "uSize"), w, h);
    glUniform4fv(glGetUniformLocation(system->shader, "uColor"), 1, color_arr);

    glBindVertexArray(system->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

SVKG_Color SVKG_Color_Get(uint32_t hex) {
    uint8_t r = (uint8_t)(hex >> 24);
    uint8_t g = (uint8_t)(hex >> 16);
    uint8_t b = (uint8_t)(hex >> 8);
    uint8_t a = (uint8_t)hex;
    return (SVKG_Color){r, g, b, a};
}
