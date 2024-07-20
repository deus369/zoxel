// save font style

// todo: save properly
unsigned char save_font_style(ecs_world_t *world, const ecs_entity_t e, char *filename) {
    zox_log(" + saving font style entity [%s]\n", zox_get_name(e))
    zox_log("   - to zox file [%s]\n", filename)
    // get full filepath
    // get binary for each font and added with seperation?
    zox_geter(e, Children, children)
    zox_log("   - font style children [%i]\n", children->length)
    return 1; // success
}

ecs_entity_t load_font_style(ecs_world_t *world, char *filename) {
    // spawn font style and spawn fonts based on data

    return 0;   // plug
}

void load_styles(ecs_world_t *world) {
    zox_font_style_default = spawn_font_style(world, prefab_font_style);
    // todo: save zox_font_style_monocraft entity into file
    // for now save
    const unsigned char loaded_ttf = initialize_ttf(world, prefab_font_style); // load in monocraft
    if (loaded_ttf) {
        save_font_style(world, zox_font_style_monocraft, "monocraft.zox");
    }
    // todo: load custom font stle files
    // zox_font_style_monocraft = load_font_style(world, "monocraft.zox");
}
