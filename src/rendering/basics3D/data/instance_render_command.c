typedef struct
{
    entity mesh;
    float4x4_array_d* transforms;
} InstanceRenderCommand;
zoxel_dynamic_array(InstanceRenderCommand)

byte has_mesh(
    InstanceRenderCommand_array_d* commands,
    entity mesh, int *index)
{
    for (size_t i = 0; i < commands->size; i++) {
        if (commands->data[i].mesh == mesh) {
            *index = i;
            return 1;
        }
    }
    return 0;
}