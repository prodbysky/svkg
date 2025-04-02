#include "GLFW/glfw3.h"
#include "svkg_audio.h"
#include <slog.h>
#include <svkg.h>

int main() {
  SVKG_Context *ctx = SVKG_ContextInit(800, 600, "Hi!");

  SVKG_Sound sound =
      SVKG_AudioSystem_LoadSound(&ctx->audio, "assets/synth.wav");

  while (!SVKG_ContextShouldQuit(ctx)) {
    if (SVKG_Input_IsKeyJustPressed(ctx, GLFW_KEY_SPACE)) {
      SVKG_AudioSystem_PlaySound(&sound);
    }
    SVKG_ContextBeginFrame(ctx);
    SVKG_ContextEndFrame(ctx);
  }

  SVKG_AudioSystem_DestroySound(&sound);
  SVKG_ContextDestroy(ctx);
}
