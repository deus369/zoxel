// miracode | monocraft
// load its point data per character
// spawn that as a font style
// todo after: rewrite font_generation - a second system - to use shapes instead of just lines
// for now just load first one
#ifdef zox_lib_ttf

ecs_entity_t spawn_font_ttf(ecs_world_t *world, FT_Face face, const float4 face_bounds, const char charcode) {
    const FT_GlyphSlot glyph = get_glyph(face, charcode);
    int length;
    byte2 *points = glyph_to_points(glyph, face_bounds, &length);
    if (length == 0) return 0;
    // zox_log(" > spawning font of points length: %i\n", length)
    const ecs_entity_t e = spawn_font(world, points, length);
    free(points);
    // zox_log(" > debugging  glyph [%c]\n", charcode)
    // if (i == 65) print_glyph(glyph);
    return e;
}

ecs_entity_t spawn_ttf_as_font_style(FT_Face face) {
    const float4 face_bounds = get_face_bounds(face);
    // enter, options, exit
    zox_instance(font_style_prefab)
    zox_name("font_style_ttf")
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, font_styles_length)
    for (int i = 0; i < font_styles_length; i++) children->value[i] = 0;
    // children->value[55] = 0; // spawn_font(world, font_space, font_space_length); // space
    for (int i = 0; i < face->num_glyphs; i++) {
        if (i >= font_styles_length) continue;
        if (!(i >= 33 && i <= 126)) continue; // only some characters can work
        int j = convert_ascii(i);
        if (j == 55) continue; // space spawns above
        const char charcode = (char) i;
        children->value[j] = spawn_font_ttf(world, face, face_bounds, charcode);
    }
    for (int i = 0; i < font_styles_length; i++) if (!children->value[i] && i != 55) children->value[i] = spawn_font(world, font_question_mark, font_question_mark_length);
    zox_modified(e, Children)
    zox_font_style = e;
    return e;
}

ecs_entity_t spawn_ttf_path_as_font_style(const FT_Library *library, const char *load_path) {
    zox_log(" > loading [%s]\n", load_path)
    FT_Face face;
    if (FT_New_Face(*library, load_path, 0, &face)) {
        fprintf(stderr, " ! error: failure in initialize_ttf [%s]\n", load_path);
        return 0;
    }
    zox_log(" + success loading ttf [%s]\n", load_path)
    const ecs_entity_t e = spawn_ttf_as_font_style(face);
    // print_glyph(get_glyph(face, '%'));
    FT_Done_Face(face);
    return e;
}

void initialize_ttf(ecs_world_t *world) {
    FT_Library library;
    if (FT_Init_FreeType(&library)) {
        fprintf(stderr, " ! error: failure in initialize_ttf\n");
        return;
    }
    char* load_directory = concat_file_path(resources_path, directory_fonts);
    char* font_ttf = concat_file_path(load_directory, default_font_ttf);
    ecs_entity_t e = spawn_ttf_path_as_font_style(&library, font_ttf);
    free(font_ttf);
    free(load_directory);
    FT_Done_FreeType(library);
}

#else

void initialize_ttf(ecs_world_t *world) {
    zox_log(" - ttf use it not enabled\n")
}

#endif
