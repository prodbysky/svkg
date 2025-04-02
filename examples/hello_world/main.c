#include "GLFW/glfw3.h"
#include "svkg_graphics.h"
#include <slog.h>
#include <svkg.h>

int main() {
    SVKG_Context *ctx = SVKG_Context_Init(800, 600, "Hi!");

    while (!SVKG_Context_ShouldQuit(ctx)) {
        if (SVKG_Input_IsKeyJustPressed(ctx, GLFW_KEY_ESCAPE)) {
            break;
        }
        SVKG_Context_BeginFrame(ctx);
        SVKG_GraphicsSystem_ClearScreen(
            SVKG_Color_Get(0x181818ff)); // Gruber-darker background my beloved
        SVKG_Context_EndFrame(ctx);
    }

    SVKG_Context_Destroy(ctx);
}
