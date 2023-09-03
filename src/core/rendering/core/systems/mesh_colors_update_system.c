void CharacterMeshUploadSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 2);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 3);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 4);
    const MeshColorRGBs *meshColorRGBs = ecs_field(it, MeshColorRGBs, 5);
    MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 7);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value == 0) continue;
        const MeshVertices *meshVertices2 = &meshVertices[i];
        const MeshColorRGBs *meshColors2 = &meshColorRGBs[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        meshDirty->value = 0;
        // if (meshColors2->length != meshVertices2->length) continue;
        MeshGPULink *meshGPULink = &meshGPULinks[i];
        ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        #ifndef zox_characters_as_cubes
            if (meshIndicies2->length == 0) {
                // clear mesh and colors buffer if zero again
                // zoxel_log(" + mesh gpu deleted [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies2->length);
                if (meshGPULink->value.x != 0 && meshGPULink->value.y != 0 && colorsGPULink->value != 0) {
                    // zoxel_log(" + mesh gpu deleted [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies2->length);
                    clear_regular_buffer(&meshGPULink->value.x);
                    clear_regular_buffer(&meshGPULink->value.y);
                    clear_regular_buffer(&colorsGPULink->value);
                    // zoxel_log(" + mesh gpu deleted 2 [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies2->length);
                }
                continue;
            }
        #endif
        if (meshGPULink->value.x == 0 && meshGPULink->value.y == 0 && colorsGPULink->value == 0) {
            // meshGPULink->value = spawn_gpu_mesh_buffers();
            meshGPULink->value.x = spawn_gpu_generic_buffer();
            meshGPULink->value.y = spawn_gpu_generic_buffer();
            colorsGPULink->value = spawn_gpu_generic_buffer();
            // zoxel_log("  > character did not have gpu mesh buffers\n");
        }
        opengl_upload_mesh_colors(meshGPULink->value, colorsGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshColors2->value, meshVertices2->length);
        #ifdef zox_errorcheck_render_characters_3D
            zoxel_log(" + character mesh gpu uploaded [%ix%i:%i] -> indicies [%i]\n", meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value, meshIndicies2->length);
        #endif
    }
} zox_declare_system(CharacterMeshUploadSystem)