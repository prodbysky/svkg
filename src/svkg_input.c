#include "slog.h"
#include <string.h>
#include <svkg_input.h>
SVKG_InputSystem SVKG_InputSystem_Init() {
    slog_info("Initialized input system");
    return (SVKG_InputSystem){0};
}
void SVKG_InputSystem_Update(SVKG_InputSystem *sys) {
    memcpy(sys->prev_keys, sys->keys, sizeof(sys->keys));
    memcpy(sys->prev_mouse_buttons, sys->mouse_buttons,
           sizeof(sys->mouse_buttons));
    sys->scroll_dy = sys->next_scroll_dy;
    sys->next_scroll_dy = 0.0;
}
