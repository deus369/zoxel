typedef struct
{
    ecs_entity_t mesh;
    float4x4_array_d* transforms;
} InstanceRenderCommand;
zoxel_dynamic_array(InstanceRenderCommand)

byte has_mesh(
    InstanceRenderCommand_array_d* commands,
    ecs_entity_t mesh, int *index)
{
    for (int i = 0; i < commands->size; i++) {
        if (commands->data[i].mesh == mesh) {
            *index = i;
            return 1;
        }
    }
    return 0;
}