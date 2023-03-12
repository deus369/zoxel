extern float4x4 main_camera_matrix;

//! Renders for material material3D_textured
void Render3DUvsSystem(ecs_iter_t *it)
{
    #ifdef zoxel_time_render_3d_uvs
        begin_timing_absolute()
    #endif
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 8);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 9);
    // later store commands per material to optimize this process
    unsigned char has_set_single_material = 0;
    Material3DTextured materialTextured3D;
    for (int i = 0; i < it->count; i++)
    {
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (meshIndicies2->length == 0)
        {
            continue;
        }
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        #ifndef voxels_terrain_multi_material
            if (!has_set_single_material)
            {
                has_set_single_material = 1;
                opengl_set_material(materialGPULink->value);
                opengl_set_texture(textureGPULink->value, false);
                opengl_shader3D_textured_set_camera_view_matrix(main_camera_matrix);
                opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value);
            }
            opengl_set_material3D_uvs_position(position->value);
            opengl_set_mesh_indicies(meshGPULink->value.x);
            opengl_set_buffer_attributes(meshGPULink->value.y, uvsGPULink->value);
            opengl_draw_triangles(meshIndicies2->length);
        #else
            opengl_set_material(materialGPULink->value);
            opengl_set_texture(textureGPULink->value, false);
            opengl_set_material3D_uvs_properties(rotation->value, scale1D->value, brightness->value);
            opengl_set_mesh_indicies(meshGPULink->value.x);
            opengl_shader3D_textured_set_camera_view_matrix(main_camera_matrix);
            opengl_set_buffer_attributes(meshGPULink->value.y, uvsGPULink->value);
            opengl_set_material3D_uvs_position(position->value);
            opengl_draw_triangles(meshIndicies2->length);
        #endif
    }
    opengl_unset_mesh();
    opengl_disable_texture(false);
    opengl_disable_opengl_program();
    #ifdef zoxel_time_render_3d_uvs
        end_timing("Render3DUvsSystem")
    #endif
}
zoxel_declare_system(Render3DUvsSystem)