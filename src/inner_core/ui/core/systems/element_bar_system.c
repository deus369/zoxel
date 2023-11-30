// todo: move this
extern unsigned char set_entity_with_text(ecs_world_t *world, ecs_entity_t e, const char* text);
extern void on_element_pixels_resized(ecs_world_t *world, ecs_entity_t e, const int2 size, unsigned char mesh_alignment);

void ElementBarSystem(ecs_iter_t *it) {
    // return;
    // if (!ecs_query_changed(NULL, it)) return;   // todo: make run on threads
    // todo: need change filter on ui render lod as well
    // todo: can_render_ui - needs to be set as a component instead of a check per each system
    zox_iter_world()
    const ElementBar *elementBars = ecs_field(it, ElementBar, 1);
    const ElementBarSize *elementBarSizes = ecs_field(it, ElementBarSize, 2);
    const Children *childrens = ecs_field(it, Children, 3);
    for (int i = 0; i < it->count; i++) {
        const Children *children = &childrens[i];
        if (!children->length) continue;
        ecs_entity_t dirty_bar = children->value[0];
        const InitializeEntityMesh *initializeEntityMesh = zox_get(dirty_bar, InitializeEntityMesh)
        if (initializeEntityMesh->value) continue;
        const TextureDirty *textureDirty = zox_get(dirty_bar, TextureDirty)
        if (textureDirty->value) continue;
        ecs_entity_t e = it->entities[i];
        if (!can_render_ui(world, e)) continue; // disabled for now causes issues
        MeshDirty *meshDirty = zox_get_mut(dirty_bar, MeshDirty)
        if (meshDirty->value) continue;
        const ElementBar *elementBar = &elementBars[i];
        const ElementBarSize *elementBarSize = &elementBarSizes[i];
        const float percentage = elementBar->value;
        const float2 scale = elementBarSize->value;
        const float left_offset = - scale.x * (1.0f - percentage) * 0.5f;
        if (zox_has(dirty_bar, MeshVertices)) {
            const MeshVertices *meshVertices = zox_get(dirty_bar, MeshVertices)
            const float test_var = (left_offset + square_vertices[2].x * scale.x * percentage);   // test right vert
            if (test_var == meshVertices->value[2].x) continue;
            MeshVertices *meshVertices2 = zox_get_mut(dirty_bar, MeshVertices)
            for (unsigned char j = 0; j < 4; j++) meshVertices2->value[j] = (float3) { left_offset + square_vertices[j].x * scale.x * percentage, square_vertices[j].y * scale.y, 0 };
            meshDirty->value = 1;
            zox_modified(dirty_bar, MeshDirty)
            zox_modified(dirty_bar, MeshVertices)
        } else if (zox_has(dirty_bar, MeshVertices2D)) {
            const PixelSize *pixelSize = zox_get(it->entities[i], PixelSize)
            PixelSize *dirty_pixel_size = zox_get_mut(dirty_bar, PixelSize)
            dirty_pixel_size->value.x = (int) (pixelSize->value.x * percentage);
            zox_modified(dirty_bar, PixelSize)
            on_element_pixels_resized(world, dirty_bar, dirty_pixel_size->value, 0);
            PixelPosition *dirty_pixel_position = zox_get_mut(dirty_bar, PixelPosition)
            dirty_pixel_position->value.x = - pixelSize->value.x / 2 + dirty_pixel_size->value.x / 2;
            // zox_log(" > dirty_pixel_position->value.x [%i]\n", dirty_pixel_position->value.x)
            zox_modified(dirty_bar, PixelPosition)
            // set text
            int percentage_i = (int) (percentage * 100);
            char text[32];
            snprintf(text, sizeof(text), "health %i%%", percentage_i);
            ecs_entity_t dirty_text = children->value[1];
            if (set_entity_with_text(world, dirty_text, text)) {
                // zox_log("health set to: [%s]\n", text)
            }
        }
    }
} zox_declare_system(ElementBarSystem)



        //float test_var = (left_offset + square_vertices[2].x * scale.x * percentage);   // test right vert
        //if (test_var != meshVertices->value[2].x) {
            // zox_log("   > dirty_bar has ? ElementBillboard %i UIHolderLink %i\n", zox_has(dirty_bar, ElementBillboard), zox_has(dirty_bar, UIHolderLink))
        //}
        // zoxel_log(" > elementbar is: %f\n", elementBar->value);
        // if (first_var < 0) zoxel_log(" > first_var is negative: %f elementBar (%f) scale (%f)\n", first_var, elementBar->value, scale.x);
        // if (elementBar->value < 0) zoxel_log(" > elementBar->value is negative: %f\n", elementBar->value);
            /*const MeshVertices2D *meshVertices = zox_get(dirty_bar, MeshVertices2D)
            const float test_var = (left_offset + square_vertices[2].x * scale.x * percentage);   // test right vert
            if (test_var == meshVertices->value[2].x) continue;
            MeshVertices2D *meshVertices2 = zox_get_mut(dirty_bar, MeshVertices2D)
            zox_log(" > meshVertices [%f]\n", meshVertices2->value[2].x)
            for (unsigned char j = 0; j < 4; j++)
                meshVertices2->value[j] = (float2) { left_offset + square_vertices[j].x * scale.x * percentage, square_vertices[j].y * scale.y };
            meshDirty->value = 1;
            zox_modified(dirty_bar, MeshDirty)
            zox_modified(dirty_bar, MeshVertices2D)*/
