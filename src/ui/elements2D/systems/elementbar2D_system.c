extern void on_element_pixels_resized(ecs_world_t *world, ecs_entity_t e, const int2 size, byte mesh_alignment);

void Elementbar2DSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ElementBar, elementBars, 1)
    zox_field_in(ElementBarSize, elementBarSizes, 2)
    zox_field_in(Children, childrens, 3)
    zox_field_in(PixelSize, pixelSizes, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Children, childrens, children)
        if (!children->length) {
            continue;
        }
        const ecs_entity_t front_bar = children->value[0];
        if (!zox_valid(front_bar)) {
            continue;
        }
        zox_geter(front_bar, InitializeElement, initializeElement)
        if (initializeElement->value) {
            continue; // removing this breaks it?!?!
        }
        // zox_field_e()
        zox_field_i(PixelSize, pixelSizes, pixelSize)
        zox_field_i(ElementBar, elementBars, elementBar)
        zox_field_i(ElementBarSize, elementBarSizes, elementBarSize)
        if (zox_has(front_bar, MeshVertices2D)) {
            // important
            if (zox_gett_value(front_bar, MeshDirty) != 0) {
                continue;
            }
            // for our elementbar2D
            if (children->length <= 1) {
                // serious problem here!!
                continue;
            }
            const float percentage = elementBar->value;
            const float2 scale = elementBarSize->value;
            // const float left_offset = - scale.x * (1.0f - percentage) * 0.5f;
            const int2 pixel_size = pixelSize->value; // zox_get_value(e, PixelSize)
            int2 front_pixel_size = zox_get_value(front_bar, PixelSize)
            PixelPosition *front_pixel_position = zox_get_mut(front_bar, PixelPosition)
            // calculate margin cause im too lazy to put it here as component yet
            int offset_x = (pixel_size.x - (pixel_size.x * scale.x)) / 2;
            float percecentage_2 = ((int) (percentage * 100)) / 100.0f; // only update per 100 units
            front_pixel_size.x = (int) floor(scale.x * pixel_size.x * percecentage_2);
            front_pixel_position->value.x = offset_x;
            zox_modified(front_bar, PixelPosition)
            on_element_pixels_resized(world, front_bar, front_pixel_size, zox_mesh_alignment_left);
            // zox_log("> elementbar updated %ix%i - position x %i percentage %f\n", front_pixel_size.x, front_pixel_size.y, offset_x, percentage)
        }
    }
} zox_declare_system(Elementbar2DSystem)