void MeshColorsUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshColorRGBs *meshColorRGBs = ecs_field(it, MeshColorRGBs, 4);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 6);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value == 0) continue;
        const MeshVertices *meshVertices2 = &meshVertices[i];
        const MeshColorRGBs *meshColors2 = &meshColorRGBs[i];
        meshDirty->value = 0;
        if (meshColors2->length != meshVertices2->length) continue;
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        MeshGPULink *meshGPULink = &meshGPULinks[i];
        ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        if (meshIndicies2->length == 0) {
            // clear mesh and colors buffer if zero again
            // zoxel_log(" + mesh gpu deleted [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies2->length);
            if (meshGPULink->value.x != 0 && meshGPULink->value.y != 0 && colorsGPULink->value != 0) {
                // zoxel_log(" + mesh gpu deleted [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies2->length);
                clear_gpu_mesh(&meshGPULink->value);
                clear_regular_buffer(&colorsGPULink->value);
                // zoxel_log(" + mesh gpu deleted 2 [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies2->length);
            }
            continue;
        }
        if (meshGPULink->value.x == 0) meshGPULink->value = spawn_gpu_mesh_buffers();
        if (colorsGPULink->value == 0) colorsGPULink->value = spawn_gpu_generic_buffer();
        opengl_upload_mesh_colors(meshGPULink->value, colorsGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshColors2->value, meshVertices2->length);
        // zoxel_log(" + [%lu] mesh gpu created [%ix%i] -> indicies [%i]\n", it->entities[i], meshGPULink->value.x, meshGPULink->value.y, meshIndicies2->length);
    }
} zox_declare_system(MeshColorsUpdateSystem)