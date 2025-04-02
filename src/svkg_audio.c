#include "slog.h"
#include <stdlib.h>
#include <svkg_audio.h>

SVKG_AudioSystem SVKG_AudioSystem_Init() {
    SVKG_AudioSystem system = {.active = true};
    system.audio_engine = calloc(1, sizeof(ma_engine));
    ma_result result;
    result = ma_engine_init(NULL, system.audio_engine);
    if (result != MA_SUCCESS) {
        slog_error(
            "Failed to initialize audio system: miniaudio error code: %zu",
            result);
        system.active = false;
        free(system.audio_engine);
        return system;
    }
    slog_info(
        "Succesfully initialized the miniaudio context and the audio system");
    return system;
}

void SVKG_AudioSystem_Destroy(SVKG_AudioSystem *system) {
    if (system->active) {
        ma_engine_uninit(system->audio_engine);
        free(system->audio_engine);
    }
}

SVKG_Sound SVKG_AudioSystem_LoadSound(SVKG_AudioSystem *system,
                                      const char *name) {
    if (!system->active) {
        return (SVKG_Sound){.valid = false};
    }
    SVKG_Sound sound = {.valid = true};
    sound.sound = calloc(1, sizeof(ma_sound));
    ma_result result = ma_sound_init_from_file(system->audio_engine, name, 0,
                                               NULL, NULL, sound.sound);
    if (result != MA_SUCCESS) {
        sound.valid = false;
        free(sound.sound);
        slog_error("Failed to load sound (%s): miniaudio error code: %zu", name,
                   result);
    }

    return sound;
}

void SVKG_AudioSystem_DestroySound(SVKG_Sound *sound) {
    if (sound->valid) {
        ma_sound_uninit(sound->sound);
        free(sound->sound);
    }
}

void SVKG_AudioSystem_PlaySound(SVKG_Sound *sound) {
    if (sound->valid) {
        ma_sound_start(sound->sound);
    }
}
