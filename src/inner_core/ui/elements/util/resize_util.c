// uses resizes the mesh
void on_resized_element(ecs_world_t *world, const ecs_entity_t e, const int2 pixel_size, const float2 canvas_size) {
    if (!headless && zox_has(e, MeshVertices2D)) {
        const MeshAlignment *meshAlignment = zox_get(e, MeshAlignment)
        MeshVertices2D *meshVertices2D = zox_get_mut(e, MeshVertices2D)
        const float2 scale2D = (float2) { pixel_size.x / canvas_size.y, pixel_size.y / canvas_size.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, scale2D);
        zox_modified(e, MeshVertices2D)
        zox_set(e, MeshDirty, { 1 })
        // for procedural textures, regenerate upon resize
        // fix for icons
        if (zox_has(e, GenerateTexture)) zox_set(e, GenerateTexture, { zox_generate_texture_trigger })
#ifdef debug_ui_scaling
        zox_log("        -> Scaling: [%fx%f]\n", scale2D.x, scale2D.y)
#endif
        if (zox_has(e, Window)) {
            const Children *children = zox_get(e, Children);
            const ecs_entity_t header = children->value[0];
            const int2 header_size = (int2) { pixel_size.x, zox_gett_value(header, PixelSize).y };
            zox_set(header, PixelSize, { header_size })
            zox_set(header, TextureSize, { header_size })
            on_resized_element(world, header, header_size, canvas_size);
            if (children->length > 1) {
                const ecs_entity_t scrollbar = children->value[1];
                if (zox_has(scrollbar, Scrollbar)) {
                    const int2 scrollbar_size = (int2) { zox_gett_value(scrollbar, PixelSize).x, pixel_size.y };
                    zox_set(scrollbar, PixelSize, { scrollbar_size })
                    zox_set(scrollbar, TextureSize, { scrollbar_size })
                    on_resized_element(world, scrollbar, scrollbar_size, canvas_size);
                    const Children *scrollbar_children = zox_get(scrollbar, Children);
                    const ecs_entity_t scrollbar_front = scrollbar_children->value[0];
                    const int bounds_y = (scrollbar_size.y / 2) - scrollbar_size.x / 2;
                    zox_set(scrollbar_front, DraggableLimits, { (int4) { 0, 0, -bounds_y, bounds_y } })
                }
            }
            const Children *header_children = zox_get(header, Children);
            if (header_children->length > 1) {
                const float2 header_position = zox_get_value(header, Position2D)
                const ecs_entity_t close_button = header_children->value[1];
                const int2 close_button_position = zox_get_value(close_button, PixelPosition)
                const float2 close_button_anchor = zox_get_value(close_button, Anchor)
                on_element_parent_updated(world, close_button, close_button_position, close_button_anchor, header_position, header_size, canvas_size);
            }
        }
    }
}
