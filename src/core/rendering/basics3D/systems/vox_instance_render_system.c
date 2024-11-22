// todo:
//   create vbo for instance stuff like particles
//   create instanced mesh prefab and spawn for grass - just has to have a tag, transform data, and point to a mesh to render
void VoxInstanceRenderSystem(ecs_iter_t *it) {
    zox_log("voxes rendering: " + it->count)
    if (!material_colored3D) return;

    ecs_entity_t grass = string_hashmap_get(files_hashmap_voxes, new_string_data("grass"));

    zox_iter_world()
    const GLuint material_link = zox_get_value(material_colored3D, MaterialGPULink)
    const MaterialColored3D *material_attributes = zox_get(material_colored3D, MaterialColored3D)

    opengl_set_material(material_link); // use program
    opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
    opengl_set_float4(material_attributes->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
    opengl_set_float(material_attributes->brightness, 1);

    // set mesh
    opengl_set_mesh_indicies(meshGPULink->value.x);
    opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
    opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
    opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);

    // zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(Position3D, position3Ds, 1)
    // zox_field_in(Color, colors, 2)

    // position
    glBindBuffer(GL_ARRAY_BUFFER, particle3D_instanced_position_buffer);
    glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, it->count * sizeof(float3), position3Ds);
    glEnableVertexAttribArray(particle3D_position_location);// Set divisor for position attribute
    glVertexAttribDivisor(particle3D_position_location, 1); // Update per instance

    // colors
    /*glBindBuffer(GL_ARRAY_BUFFER, particle3D_instanced_color_buffer);
    // glBufferData(GL_ARRAY_BUFFER, it->count * sizeof(color), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(particle3D_color_location, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*) 0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, it->count * sizeof(color), colors); // , GL_STATIC_DRAW);
    glEnableVertexAttribArray(particle3D_color_location);// Set divisor for position attribute
    glVertexAttribDivisor(particle3D_color_location, 1); // Update per instance*/

    // draw
    // wouldn't quads be less data??
    glDrawArraysInstanced(GL_TRIANGLES, 0, meshIndicies->length, it->count);

    // resets
    // glVertexAttribDivisor(particle3D_color_location, 0); // Update per instance
    instance
    //glDisableVertexAttribArray(particle3D_color_location);
    glVertexAttribDivisor(particle3D_position_location, 0); // Update per glDisableVertexAttribArray(particle3D_position_location);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // opengl_disable_buffer(material_attributes->vertex_color);
    opengl_disable_buffer(material_attributes->vertex_position);
    opengl_unset_mesh();
    opengl_disable_opengl_program();
} zox_declare_system(VoxInstanceRenderSystem
