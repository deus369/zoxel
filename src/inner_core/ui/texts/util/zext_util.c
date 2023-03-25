// #define zoxel_debug_zext_updates
ecs_entity_t spawn_zext_zigel(ecs_world_t *world, ecs_entity_t zext, int layer,
    int i, int new_children_length, unsigned char zigel_index, int font_size,
    float2 parent_position, int2 parent_pixel_size, int2 canvas_size) {
    int2 zigel_size = (int2) { font_size, font_size };
    float half_size = (zigel_size.x * new_children_length) / 2.0f;
    ecs_entity_t zigel = spawn_zigel(world, zext, zigel_index,
        (int2) { (int) (((float) zigel_size.x * i) - half_size) + zigel_size.x / 2, 0 },
        zigel_size, (float2) { 0.5f, 0.5f }, layer, parent_position, parent_pixel_size, canvas_size);
    return zigel;
}

// For reusing a zigel, set all positions again to position entire text
void set_zigel_position(ecs_world_t *world, ecs_entity_t zigel, unsigned char zigel_index,
    int font_size, float2 anchor, unsigned char new_children_length,
    float2 parent_position, int2 parent_pixel_size, int2 canvas_size) {
    int2 zigel_size = (int2) { font_size, font_size };
    float half_size = (zigel_size.x * new_children_length) / 2.0f;
    int2 local_pixel_position = (int2) { (int) (((float) zigel_size.x * zigel_index) - half_size)
        + zigel_size.x / 2, 0 };
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    float2 position2D = get_ui_real_position2D_parent(local_pixel_position, anchor,
        parent_position, parent_pixel_size, canvas_size_f, aspect_ratio);
    int2 global_pixel_position = (int2) { ceil((position2D.x / aspect_ratio + 0.5f) * canvas_size_f.x),
        ((position2D.y + 0.5f) * canvas_size_f.y) };
    ecs_set(world, zigel, PixelPosition, { local_pixel_position });
    ecs_set(world, zigel, Position2D, { position2D });
    ecs_set(world, zigel, CanvasPixelPosition, { global_pixel_position });
}

//! Dynamically updates zext by spawning/destroying zigels and updating remaining.
int spawn_zext_zigels(ecs_world_t *world, ecs_entity_t zext, Children *children, const ZextData *zextData,
    int font_size, unsigned char zext_layer, float2 parent_position, int2 parent_pixel_size) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    float2 anchor = (float2) { 0.5f, 0.5f };
    ecs_defer_begin(world);
    int reuse_count = integer_min(children->length, zextData->length);
    #ifdef zoxel_debug_zext_updates
        zoxel_log("spawn_zext_zigels :: [%i] -> [%i]; reuse [%i];\n", children->length, zextData->length, reuse_count);
    #endif
    // update the reused ones.
    for (unsigned char i = 0; i < reuse_count; i++) {
        // re set all old zigels, if index changes, regenerate font texture
        ecs_entity_t old_zigel = children->value[i];
        const ZigelIndex *zigelIndex = ecs_get(world, old_zigel, ZigelIndex);
        if (zigelIndex->value != zextData->value[i]) {
            #ifdef zoxel_debug_zigel_updates
                zoxel_log("    - zig updated [%i] [%i] -> [%i]\n", i, zigelIndex->value, zextData->value[i]);
            #endif
            ecs_set(world, old_zigel, ZigelIndex, { zextData->value[i] });
            ecs_set(world, old_zigel, GenerateTexture, { 1 });
        }
    }
    if (children->length != zextData->length) {
        unsigned char old_children_length = children->length;
        ecs_entity_t *old_children = children->value;
        unsigned char new_children_length = zextData->length;
        ecs_entity_t *new_children = (ecs_entity_t*) malloc(new_children_length * sizeof(ecs_entity_t));
        if (new_children == NULL) {
            // Something went wrong with malloc
            return 1;
        }
        for (unsigned char i = 0; i < int_min(old_children_length, new_children_length); i++) {
            ecs_entity_t old_zigel = old_children[i];
            new_children[i] = old_zigel;
            set_zigel_position(world, old_zigel, i,
                font_size, anchor, new_children_length,
                parent_position, parent_pixel_size, canvas_size);
        }
        if (new_children_length > old_children_length) {
            #ifdef zoxel_debug_zext_updates
                zoxel_log("    - spawning new_children [%i].\n", (new_children_length - old_children_length));
            #endif
            unsigned char zigel_layer = zext_layer + 1;
            for (int i = old_children_length; i < new_children_length; i++) {
                // convert normal char here to unsigned char!
                new_children[i] = spawn_zext_zigel(world, zext, zigel_layer, i, new_children_length,
                    zextData->value[i], font_size, parent_position, parent_pixel_size, canvas_size);
                // printf("Spawning new zigel at [%i]: %i\n", i, (int) zextData->value[i]);
            }
        } else if (new_children_length < old_children_length) {
            #ifdef zoxel_debug_zext_updates
                zoxel_log("    - deleting old_children [%i].\n", (old_children_length - new_children_length));
            #endif
            for (int i = new_children_length; i < old_children_length; i++)
            {
                // destroy old zigels, if resizing to less
                ecs_delete(world, old_children[i]);
            }
        }
        if (old_children) {
            free(old_children);
        }
        children->value = new_children;
        children->length = new_children_length;
    }
    #ifdef zoxel_debug_zext_updates
        else {
            zoxel_log("    - zext remained the same [%i]\n", zextData->length);
        }
    #endif
    ecs_defer_end(world);
    return 0;
}