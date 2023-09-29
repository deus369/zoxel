// #define zoxel_debug_zext_updates

int2 get_zigel_position(unsigned char index, unsigned char total_length, unsigned char font_size, unsigned char text_alignment, byte2 text_padding) {
    int2 zigel_size = (int2) { font_size, font_size };
    int half_size = zigel_size.x * total_length / 2.0f;
    int2 zigel_position = (int2) { (zigel_size.x * index - half_size) + zigel_size.x / 2, 0 };
    // default was centred
    /*if (text_alignment == zox_mesh_alignment_centred) { } else*/
    if (text_alignment == zox_mesh_alignment_right) {
        zigel_position.x -= half_size;
        zigel_position.x -= text_padding.x;
    } else if (text_alignment == zox_mesh_alignment_left) {
        zigel_position.x += half_size;
        zigel_position.x += text_padding.x;
    }
    return zigel_position;
}

// For reusing a zigel, set all positions again to position entire text
void set_zigel_position(ecs_world_t *world, ecs_entity_t zigel, unsigned char index, int font_size,  unsigned char text_alignment, byte2 text_padding,
    float2 anchor, unsigned char total_length, float2 parent_position, int2 parent_pixel_size, int2 canvas_size) {
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    int2 position = get_zigel_position(index, total_length, font_size, text_alignment, text_padding);
    ecs_set(world, zigel, PixelPosition, { position });
    float2 position2D = get_ui_real_position2D_parent(position, anchor, parent_position, parent_pixel_size, canvas_size_f, aspect_ratio);
    ecs_set(world, zigel, Position2D, { position2D });
    int2 global_pixel_position = (int2) { ceil((position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x), ((position2D.y + 0.5f) * canvas_size_f.y) };
    ecs_set(world, zigel, CanvasPixelPosition, { global_pixel_position });
}

// spawns a text character in a place
ecs_entity_t spawn_zext_zigel(ecs_world_t *world, ecs_entity_t zext, int layer, unsigned char index, int total_length, unsigned char zigel_index, int font_size, unsigned char text_alignment, byte2 text_padding, float2 parent_position, int2 parent_pixel_size, int2 canvas_size) {
    int2 zigel_size = (int2) { font_size, font_size };
    int2 position = get_zigel_position(index, total_length, font_size, text_alignment, text_padding);
    ecs_entity_t zigel = spawn_zigel(world, zext, zigel_index, position, zigel_size, (float2) { 0.5f, 0.5f }, layer, parent_position, parent_pixel_size, canvas_size);
    return zigel;
}

unsigned char is_zext_updating(ecs_world_t *world, const Children *children) {
    for (unsigned char i = 0; i < children->length; i++) { // update the reused ones
        ecs_entity_t zigel = children->value[i];
        const GenerateTexture *generateTexture = ecs_get(world, zigel, GenerateTexture);
        if (generateTexture->value) return 1;
    }
    return 0;
}

//! Dynamically updates zext by spawning/destroying zigels and updating remaining
void spawn_zext_zigels(ecs_world_t *world, ecs_entity_t zext, Children *children, const ZextData *zextData, int font_size, unsigned char text_alignment, byte2 text_padding, unsigned char zext_layer, float2 parent_position, int2 parent_pixel_size) {
    const float2 anchor = (float2) { 0.5f, 0.5f };
    const int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    unsigned char old_children_length = children->length;
    unsigned char new_children_length = zextData->length;
    int reuse_count = integer_min(old_children_length, new_children_length);
    unsigned char zigel_layer = zext_layer + 1;
    #ifdef zoxel_debug_zext_updates
        zoxel_log("spawn_zext_zigels :: [%i] -> [%i]; reuse [%i];\n", children->length, zextData->length, reuse_count);
    #endif
    // re set all old zigels, if index changes, regenerate font textureData
    for (unsigned char i = 0; i < reuse_count; i++) { // update the reused ones
        ecs_entity_t old_zigel = children->value[i];
        const ZigelIndex *zigelIndex = ecs_get(world, old_zigel, ZigelIndex);
        if (zigelIndex->value != zextData->value[i]) {
            #ifdef zoxel_debug_zigel_updates
                zoxel_log("    - zig updated [%i] [%i] -> [%i]\n", i, zigelIndex->value, zextData->value[i]);
            #endif
            ZigelIndex *zigelIndex2 = ecs_get_mut(world, old_zigel, ZigelIndex);
            GenerateTexture *generateTexture = ecs_get_mut(world, old_zigel, GenerateTexture);
            zigelIndex2->value = zextData->value[i];
            generateTexture->value = 1;
            ecs_modified(world, old_zigel, ZigelIndex);
            ecs_modified(world, old_zigel, GenerateTexture);
        }
    }
    #ifdef zoxel_debug_zext_updates
        if (children->length == zextData->length) zoxel_log("    - zext remained the same [%i]\n", zextData->length);
    #endif
    if (children->length == zextData->length) return;
    int reusing_length = int_min(old_children_length, new_children_length);
    ecs_entity_t *old_children = children->value;
    ecs_entity_t *new_children = NULL;
    if (new_children_length > 0) new_children = malloc(new_children_length * sizeof(ecs_entity_t));
    for (unsigned char i = 0; i < reusing_length; i++) {
        ecs_entity_t old_zigel = old_children[i];
        new_children[i] = old_zigel;
        set_zigel_position(world, old_zigel, i, font_size, text_alignment, text_padding, anchor, new_children_length, parent_position, parent_pixel_size, canvas_size);
    }
    if (new_children_length > old_children_length) {
        #ifdef zoxel_debug_zext_updates
            zoxel_log("    - spawning new_children [%i].\n", (new_children_length - old_children_length));
        #endif
        for (int i = old_children_length; i < new_children_length; i++) {
            unsigned char zigel_type = zextData->value[i];
            new_children[i] = spawn_zext_zigel(world, zext, zigel_layer, i, new_children_length, zigel_type, font_size, text_alignment, text_padding, parent_position, parent_pixel_size, canvas_size);
        }
    } else if (new_children_length < old_children_length) {
        #ifdef zoxel_debug_zext_updates
            zoxel_log("    - deleting old_children [%i].\n", (old_children_length - new_children_length));
        #endif
        for (int i = new_children_length; i < old_children_length; i++) zox_delete(old_children[i])
    }
    if (!old_children && new_children) total_memorys_allocated++;
    else if (old_children && !new_children) total_memorys_allocated--;
    if (old_children) free(old_children);
    children->value = new_children;
    children->length = new_children_length;
}