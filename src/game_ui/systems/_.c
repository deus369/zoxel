#include "fps_display_system.c"
#include "quads_display_system.c"
#include "device_mode_ui_system.c"
#include "debug_label_system.c"

void define_systems_game_ui(ecs_world_t *world) {
    zox_system(FpsDisplaySystem, EcsOnUpdate,
            [out] texts.TextData,
            [out] texts.ZextDirty,
            [out] FPSDisplayTicker,
            [none] FPSDisplay)
    /*zox_system(QuadsLabelSystem, EcsOnUpdate,
            [out] QuadsCount,
            [out] texts.ZextDirty,
            [out] texts.TextData,
            [none] QuadsCountLabel)*/
    zox_system(DebugLabelSystem, EcsOnStore,
            [in] players.PlayerLink,
            [in] DebugLabelData,
            [out] texts.ZextDirty,
            [out] texts.TextData,
            [none] game.u.i.GameDebugLabel)
    zox_system_1(DeviceModeUISystem, EcsOnUpdate,
            [in] inputs.DeviceMode,
            [in] inputs.DeviceModeDirty,
            [in] games.GameLink,
            [in] elements.core.CanvasLink) // note: must update before
}