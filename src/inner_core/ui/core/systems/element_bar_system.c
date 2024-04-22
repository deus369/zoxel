extern unsigned char set_entity_with_text(ecs_world_t *world, ecs_entity_t e, const char* text);
extern void on_element_pixels_resized(ecs_world_t *world, ecs_entity_t e, const int2 size, unsigned char mesh_alignment);

void ElementBarSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ElementBar, elementBars, 1)
    zox_field_in(ElementBarSize, elementBarSizes, 2)
    zox_field_in(Children, childrens, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Children, childrens, children)
        if (!children->length) continue;
        ecs_entity_t dirty_bar = children->value[0];
        const InitializeEntityMesh *initializeEntityMesh = zox_get(dirty_bar, InitializeEntityMesh)
        if (initializeEntityMesh->value) continue;
        zox_field_e()
        if (!can_render_ui(world, e)) continue; // disabled for now causes issues
        MeshDirty *meshDirty = zox_get_mut(dirty_bar, MeshDirty)
        if (meshDirty->value) continue;
        zox_field_i_in(ElementBar, elementBars, elementBar)
        zox_field_i_in(ElementBarSize, elementBarSizes, elementBarSize)
        const float percentage = elementBar->value;
        const float2 scale = elementBarSize->value;
        const float left_offset = - scale.x * (1.0f - percentage) * 0.5f;
        if (zox_has(dirty_bar, MeshVertices)) {
            // for our elementbar3D
            const MeshVertices *meshVertices = zox_get(dirty_bar, MeshVertices)
            const float test_var = (left_offset + square_vertices[2].x * scale.x * percentage);   // test right vert
            if (test_var == meshVertices->value[2].x) continue;
            MeshVertices *meshVertices2 = zox_get_mut(dirty_bar, MeshVertices)
            for (unsigned char j = 0; j < 4; j++) meshVertices2->value[j] = (float3) { left_offset + square_vertices[j].x * scale.x * percentage, square_vertices[j].y * scale.y, 0 };
            meshDirty->value = 1;
            zox_modified(dirty_bar, MeshDirty)
            zox_modified(dirty_bar, MeshVertices)
        } else if (zox_has(dirty_bar, MeshVertices2D)) {
            // for our elementbar2D
            const PixelSize *pixelSize = zox_get(it->entities[i], PixelSize)
            PixelSize *dirty_pixel_size = zox_get_mut(dirty_bar, PixelSize)
            PixelPosition *dirty_pixel_position = zox_get_mut(dirty_bar, PixelPosition)
            dirty_pixel_size->value.x = (int) (pixelSize->value.x * percentage);
            dirty_pixel_position->value.x = - pixelSize->value.x / 2 + dirty_pixel_size->value.x / 2;
            zox_modified(dirty_bar, PixelSize)
            zox_modified(dirty_bar, PixelPosition)
            int percentage_i = (int) (percentage * 100); // set text of statbar
            char text[32];
            snprintf(text, sizeof(text), "health %i%%", percentage_i);
            ecs_entity_t dirty_text = children->value[1];
            if (set_entity_with_text(world, dirty_text, text)) {
                // zox_log("health set to: [%s]\n", text)
            }
            on_element_pixels_resized(world, dirty_bar, dirty_pixel_size->value, 0);
        }
    }
} zox_declare_system(ElementBarSystem)
