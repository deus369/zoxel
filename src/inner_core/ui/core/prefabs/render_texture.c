ecs_entity_t spawn_prefab_render_texture(ecs_world_t *world) {
    zox_prefab()
    add_ui_plus_components(world, e);
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_add_tag(e, TextureRGB)
    zox_add_tag(e, RenderTexture)
    zox_prefab_add(e, CameraLink)
    return e;
}

void set_render_texture_gpu(GLuint texture_gpu_link, const int2 size) {
    // make it a render texture update system
    glBindTexture(GL_TEXTURE_2D, texture_gpu_link);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// todo: using valgrind, this causes a memory issue on close
// todo: stretch to canvas_size, size_anchor
ecs_entity_t spawn_render_texture(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const int2 canvas_size, const ecs_entity_t camera) {
    const unsigned char layer = 0;
    const ecs_entity_t parent = canvas;
    const int2 pixel_position = int2_zero;
    const float2 anchor = float2_half;
    const int2 pixel_size = canvas_size;
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab)
    zox_name("render_texture")
    zox_set(e, CameraLink, { camera })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    on_child_added(world, canvas, e);
    return e;
}
