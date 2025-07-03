#include "fps_display_system.c"
#include "quads_display_system.c"
#include "device_mode_ui_system.c"
#include "debug_label_system.c"

void zox_define_systems_game_ui(ecs_world_t *world) {
    zox_system_1(DeviceModeUISystem, EcsOnUpdate, [in] DeviceMode, [in] DeviceModeDirty, [in] GameLink, [in] CanvasLink) // note: must update before DeviceModeDirtySystem
    zox_system(FpsDisplaySystem, EcsOnUpdate, [none] FPSDisplay, [out] TextData, [out] ZextDirty, [out] FPSDisplayTicker)
    zox_system(QuadsLabelSystem, EcsOnUpdate, [none] QuadsCountLabel, [out] QuadsCount, [out] ZextDirty, [out] TextData)
    zox_system(DebugLabelSystem, EcsOnStore, [in] PlayerLink, [in] DebugLabelData, [out] ZextDirty, [out] TextData, [none] game.u.i.GameDebugLabel)
}