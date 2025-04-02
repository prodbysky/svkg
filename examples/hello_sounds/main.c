#include "GLFW/glfw3.h"
#include "svkg_audio.h"
#include <slog.h>
#include <svkg.h>

int main() {
  SVKG_Context *ctx = SVKG_Context_Init(800, 600, "Hi!");

  SVKG_Sound sound =
      SVKG_AudioSystem_LoadSound(&ctx->audio, "assets/synth.wav");

  while (!SVKG_Context_ShouldQuit(ctx)) {
    if (SVKG_Input_IsKeyJustPressed(ctx, GLFW_KEY_SPACE)) {
      SVKG_AudioSystem_PlaySound(&sound);
    }
    SVKG_Context_BeginFrame(ctx);
    SVKG_Context_EndFrame(ctx);
  }

  SVKG_AudioSystem_DestroySound(&sound);
  SVKG_Context_Destroy(ctx);
}
