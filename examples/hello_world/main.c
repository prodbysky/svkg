#include "GLFW/glfw3.h"
#include <slog.h>
#include <svkg.h>

int main() {
  SVKG_Context *ctx = SVKG_ContextInit(800, 600, "Hi!");

  while (!SVKG_ContextShouldQuit(ctx)) {
    if (SVKG_Input_IsKeyJustPressed(ctx, GLFW_KEY_ESCAPE)) {
      break;
    }
    SVKG_ContextBeginFrame(ctx);
    SVKG_ContextEndFrame(ctx);
  }

  SVKG_ContextDestroy(ctx);
}
