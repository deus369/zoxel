// save font style
#define directory_fonts "fonts"
// #define zox_log_font_io

// todo: save properly
unsigned char save_font_style(ecs_world_t *world, const ecs_entity_t e, char *resources_directory, char *filename) {
    if (!e) {
        zox_log(" ! error saving entity [%lu] invalid children [%s]\n", e, filename)
        return 0;
    }
    char* directory = concat_file_path(resources_directory, directory_fonts);
    char* directory2 = concat_file_path(directory, character_slash);
    free(directory);
    char* path = concat_file_path(directory2, filename);
    free(directory2);
#ifdef zox_log_font_io
    zox_log(" + saving font style entity [%s]\n", zox_get_name(e))
    zox_log("   - to zox file [%s]\n", filename)
    zox_log("   - directory [%s]\n", directory)
    zox_log("   - full path [%s]\n", path)
#endif
    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        zox_log(" > error saving [%s]\n", path)
        perror("Error opening file for writing");
        free(path);
        return 0;
    }
    // get full filepath
    // get binary for each font and added with seperation?
    zox_geter(e, Children, children)
    if (children == NULL) {
        zox_log(" ! error saving entity [%lu] invalid children [%s]\n", e, path)
        free(path);
        return 0;
    }
    SaveDataFontStyle data = { .length = children->length };
#ifdef zox_log_font_io
    zox_log("   - font style children [%i]\n", children->length)
#endif
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (child == 0) {
#ifdef zox_log_font_io
            zox_log(" > font [%i]\n", i)
#endif
            data.fonts[i] = (SaveDataFont) { .length = 0 };
            continue;
        }
        const FontData *fontData = zox_get(child, FontData)
#ifdef zox_log_font_io
        zox_log(" > font [%i] - points: [%i]\n", i, fontData->length)
#endif
        data.fonts[i] = (SaveDataFont) { .length = fontData->length };
        for (int j = 0; j < fontData->length; j++) data.fonts[i].points[j] = fontData->value[j];
    }
    fwrite(&data, sizeof(SaveDataFontStyle), 1, file);
    fclose(file);
    free(path);
    return 1; // success
}

ecs_entity_t spawn_font_style_save_data(ecs_world_t *world, const ecs_entity_t prefab, const SaveDataFontStyle *data) {
#ifdef zox_log_font_io
    zox_log(" > spawn_font_style_save_data fonts [%i]\n", data->length)
#endif
    const ecs_entity_t prefab_font = zox_get_value(prefab, FontLink)
    zox_instance(prefab)
    zox_name("font_style_io")
    zox_add_tag(e, TTFFontStyle)
    zox_get_muter(e, Children, children)
    resize_memory_component(Children, children, ecs_entity_t, data->length)
    for (int i = 0; i < data->length; i++) {
        if (data->fonts[i].length != 0) {
            children->value[i] = spawn_font(world, prefab_font, data->fonts[i].points, data->fonts[i].length);
#ifdef zox_log_font_io
            zox_log("   - font [%i] - points: [%i]\n", i, data->fonts[i].length)
            if (i == 0) {
                for (int j = 0; j < data->fonts[i].length; j++) {
                    zox_log("       - [0] point [%i] [%ix%i]\n", j, data->fonts[i].points[j].x, data->fonts[i].points[j].y)
                }
            }
#endif
        } else {
            children->value[i] = 0;
        }
    }
    return e;
}

ecs_entity_t load_font_style(ecs_world_t *world, char *filename) {
    // spawn font style and spawn fonts based on data
    char* directory = concat_file_path(resources_path, directory_fonts);
    char* directory_slash = concat_file_path(directory, character_slash);
    free(directory);
    char* path = concat_file_path(directory_slash, filename);
    free(directory_slash);
    FILE *file = fopen(path, "rb");
#ifdef zox_log_font_io
    zox_log(" + loading font style entity\n")
    zox_log("   - to zox file [%s]\n", filename)
    zox_log("   - directory [%s]\n", directory)
    zox_log("   - full path [%s]\n", path)
#endif
    if (file == NULL) {
        zox_log(" > file is NULL at path [%s]\n", path)
        perror("Error opening file for writing");
        free(path);
        return 0;
    }
#ifdef zox_log_font_io
    zox_log("   + success opening file\n")
#endif
    ecs_entity_t font_style = 0;
    SaveDataFontStyle data;
    size_t filesize = fread(&data, sizeof(SaveDataFontStyle), 1, file);
    if (filesize > 0) {
        font_style = spawn_font_style_save_data(world, prefab_font_style, &data);
    } else {
        zox_log(" ! filesize is 0 at [%s]\n", path)
        perror("filesize is 0");
    }
    fclose(file);
    free(path);
    return font_style;
}

void load_styles(ecs_world_t *world) {
    zox_font_style_default = spawn_font_style(world, prefab_font_style);
    // for now save
    // zox_font_style_monocraft is set in ttf initialization
    const unsigned char loaded_ttf = initialize_ttf(world, prefab_font_style); // load in monocraft
    if (loaded_ttf) {
        // save for now, testing
        // save_font_style(world, zox_font_style_monocraft, "/home/deus/zoxel/resources/", "monocraft.zox");
        // testing
        // zox_font_style_monocraft = load_font_style(world, "monocraft.zox");
    }
    zox_font_style_monocraft = load_font_style(world, "monocraft.zox");
}
