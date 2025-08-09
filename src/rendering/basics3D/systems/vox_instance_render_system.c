// todo:
//   create vbo for instance stuff like particles
//   create instanced mesh prefab and spawn for grass - just has to have a tag, transform data, and point to a mesh to render
// atm renders about 2k per frame
// when registering a new instance entity:
// create a renderer data:
//      - material
//      - ubo link
//      - transform list
// extern string_hashmap *files_hashmap_voxes;

void VoxInstanceRenderSystem(iter *it) {
    const uint max_meshes = 16;
    const uint max_transforms = 1024; // 128;
    if (!material_vox_instance) {
        return;
    }
    // zox_log("rendering [%i] instance renderers", it->count)
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TransformMatrix)
    zox_sys_in(InstanceLink)
    zox_sys_in(RenderDisabled)
    // get material
    zox_geter_value(material_vox_instance, MaterialGPULink, uint, material_link)
    if (!material_link) {
        return;
    }
    zox_geter(material_vox_instance, UboGPULink, uboGPULink)
    if (!uboGPULink->value) {
        // zox_log(" ! error with material_vox_instance uboGPULink.\n")
        return;
    }
    zox_geter(material_vox_instance, MaterialVoxInstance, material_attributes)
    InstanceRenderCommand_array_d* commands = create_InstanceRenderCommand_array_d(max_meshes);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(InstanceLink, instanceLink)
        zox_sys_i(TransformMatrix, transformMatrix)
        if (!zox_valid(instanceLink->value) || renderDisabled->value) {
            // zox_log_error("cannot render instanced mesh [%s]", zox_get_name(instanceLink->value))
            continue;
        }
        int index = 0;
        if (has_mesh(commands, instanceLink->value, &index)) {
            InstanceRenderCommand command = commands->data[index];
            add_to_float4x4_array_d(command.transforms, transformMatrix->value);
            commands->data[index] = command;
        } else {
            InstanceRenderCommand command = {
                .mesh = instanceLink->value,
                .transforms = create_float4x4_array_d(max_transforms)
            };
            if (!command.transforms) {
                // errored out
                break;
            }
            add_to_float4x4_array_d(command.transforms, transformMatrix->value);
            add_to_InstanceRenderCommand_array_d(commands, command);
            // zox_log("[%i] created new render command for [%s] at [%s]", zox_get_name(instanceLink->value), zox_get_name(it->entities[i]))
            // zox_log(" [%i] created new command %lu - %i\n", i, instanceLink->value, commands->size)
        }
    }
    // set material attributes
    zox_gpu_material(material_link);
    zox_gpu_float4x4(material_attributes->camera_matrix, render_camera_matrix);
    zox_gpu_float4(material_attributes->fog_data, get_fog_value());
    zox_gpu_float(material_attributes->brightness, 1);
    // Instance Rendering!
    for (size_t i = 0; i < commands->size; i++) {
        const InstanceRenderCommand command = commands->data[i];
        if (!command.transforms) {
            continue;
        }
        const entity mesh = command.mesh;
        if (!zox_has(mesh, MeshGPULink)) {
            zox_log_error("Invalid Instance Mesh [%s]", zox_get_name(mesh))
            continue;
        }
        zox_geter(mesh, MeshGPULink, meshGPULink)
        if (!meshGPULink->value.x || !meshGPULink->value.y) {
            zox_log_error("Invalid Instance Mesh [%s]", zox_get_name(mesh))
            continue;
        }
        zox_geter(mesh, ColorsGPULink, colorsGPULink)
        if (!colorsGPULink->value) {
            zox_log_error("[VoxInstanceRenderSystem] Error: colorsGPULink is 0 [%s]", zox_get_name(mesh))
            continue;
        }
        zox_geter(mesh, MeshIndicies, meshIndicies)
        if (meshIndicies->length == 0) {
            zox_log_error("[VoxInstanceRenderSystem] Error: meshIndicies is 0 [%s]", zox_get_name(mesh))
            continue;
        }
        // zox_log(" [%i] rendering %lu - %i - UBO %i\n", i, mesh, command.transforms->size, uboGPULink->value)
        // set mesh verts
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);

        int render_count = command.transforms->size;
        // update transform data
        glBindBuffer(GL_UNIFORM_BUFFER, uboGPULink->value);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, render_count * sizeof(float4x4), command.transforms->data);
        // draw
        glDrawElementsInstanced(GL_TRIANGLES, meshIndicies->length, GL_UNSIGNED_INT, 0, render_count);

        // reset the things
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        zox_gpu_disable_buffer(material_attributes->vertex_color);
        zox_gpu_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
    }
    // cleanup
    for (size_t i = 0; i < commands->size; i++) {
        const InstanceRenderCommand command = commands->data[i];
        dispose_float4x4_array_d(command.transforms);
    }
    dispose_InstanceRenderCommand_array_d(commands);
    zox_disable_material();
    catch_basic3D_errors("VoxInstanceRenderSystem");
} zoxd_system(VoxInstanceRenderSystem)