extern float4x4 main_camera_matrix;

//! Renders for material material3D_textured
void Render3DUvsSystem(ecs_iter_t *it)
{
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 8);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 9);
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
        if (opengl_set_material(materialGPULink->value))
        {
            opengl_set_texture(textureGPULink->value, false);
            opengl_set_mesh_indicies(meshGPULink->value.x);
            opengl_set_buffer_attributes(materialGPULink->value, meshGPULink->value.y, uvsGPULink->value);
            if (opengl_set_material3D_uvs_properties(materialGPULink->value,
                position->value, rotation->value, scale1D->value, brightness->value) == -1)
            {
                continue;
            }
            opengl_set_camera_view_matrix(materialGPULink->value, main_camera_matrix);
            opengl_draw_triangles(meshIndicies2->length);
        }
    }
    opengl_unset_mesh();
    opengl_disable_texture(false);
    opengl_disable_opengl_program();
}
zoxel_declare_system(Render3DUvsSystem)