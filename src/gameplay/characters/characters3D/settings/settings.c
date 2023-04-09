int spawn_characters3D_count = 8;
float spawn_many_radius = 0.5f;
float3 spawn_many_offset = (float3) { 0, 0, 0 };
float spawn_many_y = 0.6f;
#define model_scale 0.0006f         // 0.015f

void set_character_settings() {
    if (cpu_tier == 3) {
        spawn_characters3D_count = 512; // 2048;
        spawn_many_radius = 4.0f;
        spawn_many_y = 0.6f;
    } else if (cpu_tier == 2) {
        spawn_characters3D_count = 128;
        spawn_many_radius = 1.4f;
        spawn_many_y = 0.06f;
    } else if (cpu_tier == 1) {
        spawn_characters3D_count = 32;
        spawn_many_radius = 0.8f;
    } else {
        spawn_characters3D_count = 8;
    }
    // test single
    #ifdef zoxel_test_single_character3Ds
        spawn_characters3D_count = 1;
        spawn_many_radius = 0.0f;
        spawn_many_offset.x = 8.5f;
        spawn_many_offset.z = 8.5f;
        spawn_many_y = 1.0f;
    #endif
    zoxel_log(" > character settings set\n");
    zoxel_log("     + character spawn count is [%i]\n", spawn_characters3D_count);
}