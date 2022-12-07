extern float4x4 main_camera_matrix;

//! Renders for material material3D_textured
void Render3DUvsSystem(ecs_iter_t *it)
{
    const Position *positions = ecs_field(it, Position, 1);
    const Rotation *rotations = ecs_field(it, Rotation, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 6);
    // const UvsGPULink *uvsGPULinks = ecs_field(it, UvsGPULink, 7);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 7);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 8);
    for (int i = 0; i < it->count; i++)
    {
        const Position *position = &positions[i];
        const Rotation *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        // const UvsGPULink *uvsGPULink = &uvsGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (opengl_set_material(materialGPULink->value))
        {
            opengl_set_texture(textureGPULink->value, false);
            opengl_set_mesh(meshGPULink->value);
            // opengl_set_vertex_attributes(materialGPULink->value);
            if (opengl_set_material3D_uvs_properties(materialGPULink->value,
                position->value, rotation->value, scale1D->value, brightness->value) == -1)
            {
                continue;
            }
            opengl_set_camera_view_matrix(materialGPULink->value, main_camera_matrix);
            opengl_draw_triangles(meshIndicies2->length);
        }
    }
    //opengl_disable_texture(false);
    //opengl_disable_opengl_program();
}
ECS_SYSTEM_DECLARE(Render3DUvsSystem);

            /*for (int j = 0; j < main_cameras_count; j++)
            {
                ecs_entity_t camera_entity = main_cameras[j];
                if (!ecs_is_valid(world, camera_entity))
                {
                    continue;
                }
                // printf("Rendering! [%i]\n", j);
                opengl_set_camera_view_matrix(materialGPULink->value,
                    ecs_get(world, camera_entity, ViewMatrix)->value);
                opengl_draw_triangles(meshIndicies2->length);
            }*/
            // printf("Rendering [%lu] mesh with texture: %i\n", (long int) it->entities[i], textureGPULink->value);