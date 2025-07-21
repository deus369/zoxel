typedef struct {
    float3 camera_euler;
    float4 camera_rotation_local;
} SaveDataCamera;
SaveDataCamera camera_save;
create_load_and_save_functions(SaveDataCamera, camera)