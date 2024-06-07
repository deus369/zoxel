extern unsigned char set_entity_with_text(ecs_world_t *world, ecs_entity_t e, const char* text);
extern void on_element_pixels_resized(ecs_world_t *world, ecs_entity_t e, const int2 size, unsigned char mesh_alignment);

void ElementBarSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ElementBar, elementBars, 1)
    zox_field_in(ElementBarSize, elementBarSizes, 2)
    zox_field_in(Children, childrens, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Children, childrens, children)
        if (!children->length) continue;
        const ecs_entity_t front_bar = children->value[0];
        if (!zox_valid(front_bar)) continue;
        const InitializeElement *initializeElement = zox_get(front_bar, InitializeElement)
        if (initializeElement->value) continue; // removing this breaks it?!?!
        zox_field_e()
        // unsigned char is_2D = zox_has(front_bar, MeshVertices2D);
        if (!can_render_ui(world, e)) continue; // disabled for now causes issues
        zox_field_i(ElementBar, elementBars, elementBar)
        zox_field_i(ElementBarSize, elementBarSizes, elementBarSize)
        const float percentage = elementBar->value;
        const float2 scale = elementBarSize->value;
        const float left_offset = - scale.x * (1.0f - percentage) * 0.5f;
        if (zox_has(front_bar, MeshVertices)) {
            // todo: seperate this into a seperate system for 3D frontbars
            MeshDirty *meshDirty = zox_get_mut(front_bar, MeshDirty)
            if (meshDirty->value) continue;
            // for our elementbar3D
            // const MeshVertices *meshVertices = zox_get(front_bar, MeshVertices)
            // const float test_var = (left_offset + square_vertices[2].x * scale.x * percentage);   // test right vert
            // if (test_var == meshVertices->value[2].x) continue;
            MeshVertices *meshVertices2 = zox_get_mut(front_bar, MeshVertices)
            for (unsigned char j = 0; j < 4; j++) meshVertices2->value[j] = (float3) { left_offset + square_vertices[j].x * scale.x * percentage, square_vertices[j].y * scale.y, 0 };
            meshDirty->value = 1;
            zox_modified(front_bar, MeshDirty)
            zox_modified(front_bar, MeshVertices)
        } else if (zox_has(front_bar, MeshVertices2D)) {
            // todo: seperate this into a seperate system
            // for our elementbar2D
            if (children->length <= 1) {
                // serious problem here!!
                continue;
            }
            const ecs_entity_t bar_text = children->value[1];
            char text[16];
            snprintf(text, 16, "health [%i]", (int) (percentage * 100));
            if (!set_entity_with_text(world, bar_text, text)) continue; // if same text, no need resize
            const int2 pixel_size = zox_get_value(e, PixelSize)
            int2 front_pixel_size = zox_get_value(front_bar, PixelSize)
            PixelPosition *front_pixel_position = zox_get_mut(front_bar, PixelPosition)
            // calculate margin cause im too lazy to put it here as component yet
            int offset_x = (pixel_size.x - (pixel_size.x * scale.x)) / 2;
            float percecentage_2 = ((int) (percentage * 100)) / 100.0f; // only update per 100 units
            front_pixel_size.x = (int) floor(scale.x * pixel_size.x * percecentage_2);
            front_pixel_position->value.x = offset_x;
            zox_modified(front_bar, PixelPosition)
            on_element_pixels_resized(world, front_bar, front_pixel_size, zox_mesh_alignment_left);
        }
    }
} zox_declare_system(ElementBarSystem)
