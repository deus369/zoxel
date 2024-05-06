// miracode | monocraft
const char *default_font_ttf = "resources/fonts/miracode.ttf";
// load its point data per character
// spawn that as a font style
// todo after: rewrite font_generation - a second system - to use shapes instead of just lines
// for now just load first one

#ifdef zox_lib_ttf

#include <ft2build.h>
#include FT_FREETYPE_H
const float point_font_margins = 0.04f;

float4 get_glyph_bounds(const FT_GlyphSlot glyph) {
    float4 bounds;
    if (glyph->outline.n_points == 0) return float4_zero;
    bounds.x = bounds.y = glyph->outline.points[0].x;
    bounds.z = bounds.w = glyph->outline.points[0].y;
    for (int i = 1; i < glyph->outline.n_points; i++) {
        const int x = glyph->outline.points[i].x;
        const int y = glyph->outline.points[i].y;
        if (x < bounds.x) bounds.x = x;
        if (x > bounds.y) bounds.y = x;
        if (y < bounds.z) bounds.z = y;
        if (y > bounds.w) bounds.w = y;
    }
    return bounds;
}

float4 get_face_bounds(FT_Face face) {
    float4 bounds;
    for (int i = 0; i < face->num_glyphs; i++) {
        if (!((i >= 48 && i <= 57) || (i >= 65 && i <= 90) || (i >= 97 && i <= 122) || i == 95)) continue;
        if (i == 98) continue;
        FT_Load_Glyph(face, i, FT_LOAD_DEFAULT); // Load the glyph
        FT_GlyphSlot glyph = face->glyph;
        const float4 glyph_bounds = get_glyph_bounds(glyph);
        if (i == 65) {
            bounds = glyph_bounds;
        } else {
            if (glyph_bounds.x < bounds.x) bounds.x = glyph_bounds.x;
            if (glyph_bounds.y > bounds.y) bounds.y = glyph_bounds.y;
            if (glyph_bounds.z < bounds.z) bounds.z = glyph_bounds.z;
            if ( glyph_bounds.w > bounds.w) bounds.w = glyph_bounds.w;
        }
    }
    return bounds;
}

int2 get_glyph_size(const FT_GlyphSlot glyph) {
    return (int2) { glyph->metrics.width, glyph->metrics.height };
}

float2 get_glyph_margins(const FT_GlyphSlot glyph) {
    return (float2) { glyph->metrics.horiBearingX, glyph->metrics.horiBearingY };
}

byte2 glyph_point_to_byte2(FT_Vector point_, const int2 glyph_size, const float4 glyph_bounds) {
    float2 point = (float2) { point_.x, point_.y };
    point.x /= (float) glyph_bounds.y;
    point.y /= (float) glyph_bounds.w;
    // fix algorithm to be fine with 255
    point.x *= 255;
    point.y *= 255;
    point.x = point.x * (1 - point_font_margins * 2) + point_font_margins;
    point.y = point.y * (1 - point_font_margins * 2) + point_font_margins;
    int2 point_i2 = float2_to_int2(point);
    return int2_to_byte2(point_i2);
}

void print_glyph(const FT_GlyphSlot glyph) {
    const int2 glyph_size = get_glyph_size(glyph);
    const float2 glyph_margins = get_glyph_margins(glyph);
    const float4 glyph_bounds = get_glyph_bounds(glyph);
    zox_log(" + glyph size [%ix%i]\n", glyph_size.x, glyph_size.y)
    zox_log(" + glyph margins [%fx%f]\n", glyph_margins.x, glyph_margins.y)
    zox_log(" + glyph bounds [%fx%f] [%fx%f]\n", glyph_bounds.x, glyph_bounds.y, glyph_bounds.z, glyph_bounds.w)
    zox_log(" + glyph points [%i]:\n", glyph->outline.n_points);
    for (int j = 0; j < glyph->outline.n_points; j++) {
        FT_Vector point = glyph->outline.points[j];
        byte2 converted_point = glyph_point_to_byte2(point, glyph_size, glyph_bounds);
        zox_log("    - [%i]: [%ld, %ld]\n", j, point.x, point.y)
        zox_log("       - [%i]: [%i, %i]\n", j, converted_point.x, converted_point.y)
    }
    /*int start_point_index = 0;
    for (int c = 0; c < glyph->outline.n_contours; c++) {
        int contour_end = glyph->outline.contours[c];
        zox_log("   - shape index [%i] to [%i]\n", start_point_index, contour_end)
        for (int i = start_point_index; i <= contour_end; i++) {
            FT_Vector point_a = glyph->outline.points[i];
            FT_Vector point_b;
            if (i == contour_end) point_b = glyph->outline.points[start_point_index];
            else point_b = glyph->outline.points[i + 1];
            zox_log("       - line [%ix%i] to [%ix%i]\n", point_a.x, point_a.y, point_b.x, point_b.y)
        }
        start_point_index = contour_end + 1;
    }*/
}

FT_UInt get_glyph_index(FT_Face face, const char charcode) {
    return FT_Get_Char_Index(face, (FT_ULong) charcode);
}

FT_GlyphSlot get_glyph(FT_Face face, const char charcode) {
    const FT_UInt index = get_glyph_index(face, charcode);
    if (FT_Load_Glyph(face, index, FT_LOAD_DEFAULT)) {
        fprintf(stderr, "Error: Could not load glyph %d\n", index);
        return 0;
    }
    return face->glyph;
}

byte2* glyph_to_points(const FT_GlyphSlot glyph, const float4 face_bounds, int *length) {
    const int2 glyph_size = get_glyph_size(glyph);
    const float2 glyph_margins = get_glyph_margins(glyph);
    const float4 glyph_bounds = get_glyph_bounds(glyph);
    *length = 0;
    int start_point_index = 0;
    for (int c = 0; c < glyph->outline.n_contours; c++) {
        int contour_end = glyph->outline.contours[c];
        for (int i = start_point_index; i <= contour_end; i++) {
            *length += 2;
        }
        start_point_index = contour_end + 1;
    }
    byte2 *points = malloc(*length * sizeof(byte2));
    int k = 0;
    start_point_index = 0;
    for (int c = 0; c < glyph->outline.n_contours; c++) {
        int contour_end = glyph->outline.contours[c];
        for (int i = start_point_index; i <= contour_end; i++) {
            FT_Vector point_a = glyph->outline.points[i];
            FT_Vector point_b;
            if (i == contour_end) point_b = glyph->outline.points[start_point_index];
            else point_b = glyph->outline.points[i + 1];
            points[k] = glyph_point_to_byte2(point_a, glyph_size, face_bounds);
            points[k + 1] = glyph_point_to_byte2(point_b, glyph_size, face_bounds);
            k += 2;
        }
        start_point_index = contour_end + 1;
    }
    return points;
}

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
    FT_Done_Face(face);
    return e;
}

void initialize_ttf(ecs_world_t *world) {
    FT_Library library;
    if (FT_Init_FreeType(&library)) {
        fprintf(stderr, " ! error: failure in initialize_ttf\n");
        return;
    }
    ecs_entity_t e = spawn_ttf_path_as_font_style(&library, default_font_ttf);
    FT_Done_FreeType(library);
}

#else

void initialize_ttf(ecs_world_t *world) {
    zox_log(" - ttf use it not enabled\n")
}

#endif

/*if (i >= 97 && i <= 122) j = i - 97 + 1; // lowercase
else if (i >= 65 && i <= 90) j = i - 65 + 27; // upper case
else if (i >= 48 && i <= 57) j = convert_ascii(i); // numbers
else if (i >= 33 && i <= 47) j = convert_ascii(i); // special characters
else if (i >= 58 && i <= 64) j = convert_ascii(i); // special characters*/
// print_glyph(get_glyph(face, '!'));
// print_glyph(get_glyph(face, 'I'));
// print_glyph(get_glyph(face, 'i'));
// print_glyph(get_glyph(face, 'g'));
// print_glyph(get_glyph(face, '.'));
// print_glyph(get_glyph(face, '^'));
// print_glyph(get_glyph(face, 'D'));
