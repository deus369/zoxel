// uses resizes the mesh
void on_resized_element(ecs_world_t *world,
    const ecs_entity_t e,
    const int2 pixel_size,
    const float2 canvas_size)
{
    if (!headless && zox_has(e, MeshVertices2D)) {
        zox_geter(e, MeshAlignment, meshAlignment)
        zox_get_muter(e, MeshVertices2D, meshVertices2D)
        const float2 size2D = (float2) { pixel_size.x / canvas_size.y, pixel_size.y / canvas_size.y };
        set_mesh_vertices_scale2D(meshVertices2D, get_aligned_mesh2D(meshAlignment->value), 4, size2D);
        zox_set(e, MeshDirty, { mesh_state_trigger2 })
        // for procedural textures, regenerate upon resize
        // fix for icons
        if (zox_has(e, GenerateTexture)) {
            zox_set(e, GenerateTexture, { zox_generate_texture_trigger })
        }
        if (zox_has(e, Window)) {
            zox_geter(e, Children, children)
            const ecs_entity_t header = children->value[0];
            zox_geter_value(e, PixelSize, int2, header_size)
            const int2 new_header_size = (int2) {
                pixel_size.x,
                header_size.y
            };
            zox_set(header, PixelSize, { new_header_size })
            zox_set(header, TextureSize, { new_header_size })
            on_resized_element(world, header, new_header_size, canvas_size);
            zox_geter(header, Children, header_children)
            if (header_children->length > 1) {
                zox_geter_value(header, Position2D, float2, header_position)
                const ecs_entity_t close_button = header_children->value[1];
                const int2 close_button_position = zox_get_value(close_button, PixelPosition)
                zox_geter_value(close_button, Anchor, float2, close_button_anchor)
                on_element_parent_updated(world,
                    close_button,
                    close_button_position,
                    close_button_anchor,
                    header_position,
                    new_header_size,
                    canvas_size);
            }
            // scrollbar
            const ecs_entity_t scrollbar = children->length > 1 ? children->value[1] : 0;
            if (scrollbar && zox_has(scrollbar, Scrollbar)) {
                const int2 scrollbar_size = (int2) { zox_gett_value(scrollbar, PixelSize).x, pixel_size.y };
                zox_set(scrollbar, PixelSize, { scrollbar_size })
                zox_set(scrollbar, TextureSize, { scrollbar_size })
                on_resized_element(world, scrollbar, scrollbar_size, canvas_size);
                zox_geter(scrollbar, Children, scrollbar_children)
                const ecs_entity_t scrollbar_front = scrollbar_children->value[0];
                const int bounds_y = (scrollbar_size.y / 2) - scrollbar_size.x / 2;
                zox_set(scrollbar_front, DraggableLimits, { (int4) { 0, 0, -bounds_y, bounds_y } })
            }
        }
    }
}
