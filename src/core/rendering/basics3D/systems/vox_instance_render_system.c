// todo:
//   create vbo for instance stuff like particles
//   create instanced mesh prefab and spawn for grass - just has to have a tag, transform data, and point to a mesh to render
// atm renders about 2k per frame
extern string_hashmap *files_hashmap_voxes;

void VoxInstanceRenderSystem(ecs_iter_t *it) {
    zox_iter_world()
    if (material_vox_instance == 0) {
        zox_log(" ! error with vox instance material_vox_instance.")
        return;
    }

    // get material
    const GLuint material_link = zox_get_value(material_vox_instance, MaterialGPULink)
    zox_geter(material_vox_instance, MaterialVoxInstance, material_attributes)

    // get model we are mass rendering
    ecs_entity_t grass = string_hashmap_get(files_hashmap_voxes, new_string_data("grass"));
    if (grass == 0) {
        zox_log("grass model not found.\n")
    }
    zox_geter(grass, MeshGPULink, meshGPULink)
    if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) {
        zox_log(" ! error with vox instance mesh link.\n")
        return;
    }
    zox_geter(grass, ColorsGPULink, colorsGPULink)
    if (colorsGPULink->value == 0) {
        zox_log(" ! error with vox instance colors link.\n")
        return;
    }
    zox_geter(grass, MeshIndicies, meshIndicies)
    if (meshIndicies->length == 0) {
        zox_log(" ! error with vox instance meshIndicies.\n")
        return;
    }

    // set material attributes
    opengl_set_material(material_link);
    opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
    opengl_set_float4(material_attributes->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
    opengl_set_float(material_attributes->brightness, 1);

    // set mesh verts
    opengl_set_mesh_indicies(meshGPULink->value.x);
    opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
    opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);

    // instance data
    zox_field_in(TransformMatrix, instance_transforms, 1)

    // update transform data
    glBindBuffer(GL_UNIFORM_BUFFER, vox_instance_transform_link);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, it->count * sizeof(float4x4), instance_transforms);

    // draw
    glDrawElementsInstanced(GL_TRIANGLES, meshIndicies->length, GL_UNSIGNED_INT, 0, it->count); // use Elements when relying on indicies

    // reset the things
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    opengl_disable_buffer(material_attributes->vertex_color);
    opengl_disable_buffer(material_attributes->vertex_position);
    opengl_unset_mesh();
    opengl_disable_opengl_program();

    // zox_log("grasses: %i\n", it->count)
} zox_declare_system(VoxInstanceRenderSystem)


// wouldn't quads be less data??
// if (check_opengl_error_unlogged() != 0) {
//     zox_log(" > vox instance glDrawArraysInstanced\n");
// }
