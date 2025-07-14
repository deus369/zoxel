void Render3DSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(TransformMatrix)
    zox_sys_in(Brightness)
    zox_sys_in(MeshGPULink)
    zox_sys_in(MeshIndicies)
    zox_sys_in(MaterialGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(MaterialGPULink, materialGPULink)
        zox_sys_i(Brightness, brightness)
        zox_sys_i(TransformMatrix, transformMatrix)
        if (meshIndicies->length == 0 || meshGPULink->value.x == 0 || meshGPULink->value.y == 0 || materialGPULink->value == 0) {
            continue;
        }
        MaterialBasic3D attributes = create_MaterialBasic3D(materialGPULink->value);
        opengl_set_material(materialGPULink->value);
        opengl_set_matrix(attributes.camera_matrix, render_camera_matrix);
        opengl_set_float4(attributes.fog_data, get_fog_value());
        opengl_set_float(attributes.brightness, brightness->value);
        opengl_set_matrix(attributes.transform_matrix, transformMatrix->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes.vertex_position, meshGPULink->value.y);
        opengl_render(meshIndicies->length);
        opengl_disable_buffer(attributes.vertex_position);
        opengl_unset_mesh();
        opengl_disable_opengl_program();
    }
} zox_declare_system(Render3DSystem)
