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
        float percentage = elementBar->value;
        float2 scale = elementBarSize->value;
        float left_offset = - scale.x * (1.0f - percentage) * 0.5f;
        const MeshVertices *meshVertices = zox_get(dirty_bar, MeshVertices)
        float test_var = (left_offset + square_vertices[2].x * scale.x * percentage);   // test right vert
        if (test_var == meshVertices->value[2].x) continue;
        MeshVertices *meshVertices2 = zox_get_mut(dirty_bar, MeshVertices)
        for (unsigned char j = 0; j < 4; j++)
            meshVertices2->value[j] = (float3) { left_offset + square_vertices[j].x * scale.x * percentage, square_vertices[j].y * scale.y, 0 };
        meshDirty->value = 1;
        zox_modified(dirty_bar, MeshDirty)
        zox_modified(dirty_bar, MeshVertices)

        //float test_var = (left_offset + square_vertices[2].x * scale.x * percentage);   // test right vert
        //if (test_var != meshVertices->value[2].x) {
            // zox_log("   > dirty_bar has ? ElementBillboard %i UIHolderLink %i\n", zox_has(dirty_bar, ElementBillboard), zox_has(dirty_bar, UIHolderLink))
        //}
        // zoxel_log(" > elementbar is: %f\n", elementBar->value);
        // if (first_var < 0) zoxel_log(" > first_var is negative: %f elementBar (%f) scale (%f)\n", first_var, elementBar->value, scale.x);
        // if (elementBar->value < 0) zoxel_log(" > elementBar->value is negative: %f\n", elementBar->value);
    }
} zox_declare_system(ElementBarSystem)
