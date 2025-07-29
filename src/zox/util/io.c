void load_files_zox(ecs_world_t *world) {
    load_settings(world, game_name);
    load_files_shaders(world);
    load_files_fonts(world);
#ifdef zox_mod_textures
    load_files_textures(world);
#endif
#ifdef zox_mod_sounds
    load_files_sounds(world);
#endif
#ifdef zox_mod_voxes
    load_files_voxes(world);
#endif
}