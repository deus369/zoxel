// todo:
//   create vbo for instance stuff like particles
//   create instanced mesh prefab and spawn for grass - just has to have a tag, transform data, and point to a mesh to render
// atm renders about 2k per frame
// when registering a new instance entity:
// create a renderer data:
//      - material
//      - ubo link
//      - transform list
//
extern string_hashmap *files_hashmap_voxes;

typedef struct
{
    ecs_entity_t mesh;
    float4x4_array_d* transforms;
} InstanceRenderCommand;
zoxel_dynamic_array(InstanceRenderCommand)

byte has_mesh(InstanceRenderCommand_array_d* commands, ecs_entity_t mesh, int *index) {
    for (int i = 0; i < commands->size; i++) {
        if (commands->data[i].mesh == mesh) {
            *index = i;
            return 1;
        }
    }
    return 0;
}

void VoxInstanceRenderSystem(ecs_iter_t *it) {
    if (material_vox_instance == 0 || it->count == 0) {
        zox_log(" ! error with vox instance material_vox_instance.")
        return;
    }
    // zox_log("instances: %i\n", it->count)
    zox_field_world()
    // create dynamic array of transforms
    InstanceRenderCommand_array_d* commands = create_InstanceRenderCommand_array_d(16);
    zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(InstanceLink, instanceLinks, 2) // this should be instance link per lod level?
    zox_field_in(RenderDisabled, renderDisableds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(InstanceLink, instanceLinks, instanceLink)
        if (!instanceLink->value) continue;
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        int index = 0;
        if (has_mesh(commands, instanceLink->value, &index)) {
            InstanceRenderCommand command = commands->data[index];
            add_to_float4x4_array_d(command.transforms, transformMatrix->value);
            commands->data[index] = command;
        } else {
            InstanceRenderCommand command = {
                .mesh = instanceLink->value,
                .transforms = create_float4x4_array_d(128)
            };
            add_to_float4x4_array_d(command.transforms, transformMatrix->value);
            add_to_InstanceRenderCommand_array_d(commands, command);
            // zox_log(" [%i] created new command %lu - %i\n", i, instanceLink->value, commands->size)
        }
    }

    // get material
    const GLuint material_link = zox_get_value(material_vox_instance, MaterialGPULink)
    zox_geter(material_vox_instance, MaterialVoxInstance, material_attributes)
    zox_geter(material_vox_instance, UboGPULink, uboGPULink)
    if (uboGPULink->value == 0) {
        zox_log(" ! error with material_vox_instance uboGPULink.\n")
        return;
    }
    // set material attributes
    opengl_set_material(material_link);
    opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
    opengl_set_float4(material_attributes->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
    opengl_set_float(material_attributes->brightness, 1);

    // render now
    for (int i = 0; i < commands->size; i++) {
        const InstanceRenderCommand command = commands->data[i];
        const ecs_entity_t mesh = command.mesh;
        /*zox_geter(mesh, UboGPULink, uboGPULink)
        if (uboGPULink->value == 0) {
            zox_log(" ! error with vox instance uboGPULink.\n")
            continue;
        }*/
        zox_geter(mesh, MeshGPULink, meshGPULink)
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) {
            zox_log(" ! error with vox instance mesh link.\n")
            continue;
        }
        zox_geter(mesh, ColorsGPULink, colorsGPULink)
        if (colorsGPULink->value == 0) {
            zox_log(" ! error with vox instance colors link.\n")
            continue;
        }
        zox_geter(mesh, MeshIndicies, meshIndicies)
        if (meshIndicies->length == 0) {
            zox_log(" ! error with vox instance meshIndicies.\n")
            continue;
        }

        // zox_log(" [%i] rendering %lu - %i - UBO %i\n", i, mesh, command.transforms->size, uboGPULink->value)

        // set mesh verts
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);

        // command.transforms->data = realloc(command.transforms->data, command.transforms->size * sizeof(float4x4));
        int render_count = command.transforms->size;
        // update transform data
        glBindBuffer(GL_UNIFORM_BUFFER, uboGPULink->value);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, render_count * sizeof(float4x4), command.transforms->data);
        // draw
        glDrawElementsInstanced(GL_TRIANGLES, meshIndicies->length, GL_UNSIGNED_INT, 0, render_count);
        // reset the things
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        opengl_disable_buffer(material_attributes->vertex_color);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
    }
    for (int i = 0; i < commands->size; i++) {
        const InstanceRenderCommand command = commands->data[i];
        dispose_float4x4_array_d(command.transforms);
    }
    dispose_InstanceRenderCommand_array_d(commands);
    opengl_disable_opengl_program();
} zox_declare_system(VoxInstanceRenderSystem)


// wouldn't quads be less data??
// if (check_opengl_error_unlogged() != 0) {
//     zox_log(" > vox instance glDrawArraysInstanced\n");
// }
