// Once main thread is fixed, update to gpu in this system.
// extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
// todo: update this in thread
void MeshUvsUpdateSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(NULL, it)) return;
    #ifdef zoxel_time_mesh_uvs_update_system
        int update_count = 0;
        begin_timing()
    #endif
    MeshDirty *meshDirtys = ecs_field(it, MeshDirty, 1);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 2);
    const MeshVertices *meshVertices = ecs_field(it, MeshVertices, 3);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    const MeshUVs *meshUVs = ecs_field(it, MeshUVs, 4);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    const MeshColorRGBs *meshColorRGBs = ecs_field(it, MeshColorRGBs, 5);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 8);
    for (int i = 0; i < it->count; i++) {
        MeshDirty *meshDirty = &meshDirtys[i];
        if (meshDirty->value != 1) continue;
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        const MeshVertices *meshVertices2 = &meshVertices[i];
        const MeshUVs *meshUVs2 = &meshUVs[i];
        const MeshColorRGBs *meshColorRGBs2 = &meshColorRGBs[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        opengl_upload_shader3D_textured(meshGPULink->value, uvsGPULink->value, colorsGPULink->value, meshIndicies2->value, meshIndicies2->length, meshVertices2->value, meshVertices2->length, meshUVs2->value, meshColorRGBs2->value);
        meshDirty->value = 0;
        /*zoxel_log(" o> mesh3D_textured built [%lu] [%i:%i:%i:%i]\n", it->entities[i], meshIndicies2->length, meshVertices2->length, meshUVs2->length, meshColorRGBs2->length);
        const Position3D *position3D = ecs_get(it->world, it->entities[i], Position3D);
        spawn_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, 0, 1 }), 2, 6);*/
        #ifdef zoxel_time_mesh_uvs_update_system
            did_do_timing()
            update_count++;
        #endif
        // zoxel_log(" > uploaded shader texture3D [%lu] :: [%ix%i:%i]\n", it->entities[i], meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value);
    }
    #ifdef zoxel_time_mesh_uvs_update_system
        end_timing("    - mesh_uvs_update_system")
        if (did_do) zoxel_log("        - updated chunk meshes [%i]\n", update_count);
    #endif
} zox_declare_system(MeshUvsUpdateSystem)