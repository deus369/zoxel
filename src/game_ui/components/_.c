zoxc_byte(MenuType);
zox_tag(MenuMain);
zox_tag(MenuOptions);
zox_tag(MenuPaused);
zox_tag(MenuGame);
zox_tag(MenuGameTouch);
zox_tag(MenuStart);
zox_tag(FPSDisplay);
zox_tag(QuadsCountLabel);
zox_tag(GameDebugLabel);
zox_tag(Profiler);
zox_tag(Taskbar);
zox_tag(MenuNewRealm);
zoxc_byte(HitType);
zoxc_int(QuadsCount);
zoxc_double(FPSDisplayTicker);
zoxc(DebugLabelData, DebugLabelEvent);
// #include "debug_label_data.c"

void define_components_game_ui(ecs_world_t *world) {
    zoxd_byte(MenuType);
    zox_define_tag(MenuMain);
    zox_define_tag(MenuOptions);
    zox_define_tag(MenuPaused);
    zox_define_tag(MenuGame);
    zox_define_tag(MenuGameTouch);
    zox_define_tag(MenuStart);
    zox_define_tag(FPSDisplay);
    zox_define_tag(QuadsCountLabel);
    zox_define_tag(GameDebugLabel);
    zox_define_tag(Profiler);
    zox_define_tag(Taskbar);
    zox_define_tag(MenuNewRealm);;
    zoxd_byte(HitType);
    zox_define_component_int(QuadsCount);
    zox_define_component_double(FPSDisplayTicker);
    zox_define_component(DebugLabelData);
}