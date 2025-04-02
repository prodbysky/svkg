cmake_minimum_required(VERSION 3.15)
project(svkg VERSION 1.0.0 LANGUAGES C CXX)

# Set C standard (adjust if needed)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Library output directory
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(
    include/
    extern/glad/include/
    extern/glfw/include/
    extern/miniaudio/
    extern/imgui/backends/
    extern/imgui_bindings/
    extern/slog/src/
    extern/imgui/
)

add_library(svkg STATIC
    src/svkg.c
    src/svkg_input.c
)

add_subdirectory(extern/glfw)
target_link_libraries(svkg PRIVATE glfw)

add_subdirectory(extern/slog)
target_link_libraries(svkg PRIVATE slog)

add_library(glad STATIC extern/glad/src/glad.c)
target_include_directories(glad PUBLIC extern/glad/include)
target_link_libraries(svkg PRIVATE glad)

target_include_directories(svkg PRIVATE extern/miniaudio)

file(GLOB IMGUI_SOURCES
    extern/imgui/*.cpp
    extern/imgui_bindings/dcimgui.cpp
    extern/imgui_bindings/dcimgui_impl_opengl3.cpp
)

list(REMOVE_ITEM IMGUI_SOURCES extern/imgui/imgui_demo.cpp)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC 
    extern/imgui
    extern/imgui_bindings
)
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(svkg PRIVATE imgui)

if(WIN32)
    target_link_libraries(svkg PRIVATE gdi32 opengl32)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(svkg PRIVATE
        ${COCOA_LIBRARY}
        ${OPENGL_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
    )
elseif(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    find_package(X11 REQUIRED)
    target_link_libraries(svkg PRIVATE
        Threads::Threads
        ${X11_LIBRARIES}
        GL
        m
        dl
    )
endif()

option(SVKG_BUILD_EXAMPLES "Build example programs" ON)

if(SVKG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
