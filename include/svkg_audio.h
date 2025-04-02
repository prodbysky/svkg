#ifndef SVKG_AUDIO_H
#define SVKG_AUDIO_H
#include <miniaudio.h>
#include <stdbool.h>

typedef struct {
    ma_engine* audio_engine;
    bool active;
} SVKG_AudioSystem;

typedef struct {
    ma_sound* sound;
    bool valid;
} SVKG_Sound;

SVKG_AudioSystem SVKG_AudioSystem_Init();
void SVKG_AudioSystem_Destroy(SVKG_AudioSystem* system);
SVKG_Sound SVKG_AudioSystem_LoadSound(SVKG_AudioSystem *system,
                                      const char *name);
void SVKG_AudioSystem_DestroySound(SVKG_Sound *sound);
void SVKG_AudioSystem_PlaySound(SVKG_Sound* sound);



#endif
