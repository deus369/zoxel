int spawn_characters3D_count = 8;
float spawn_many_radius = 0.5f;
float3 spawn_many_offset = (float3) { 0, 0, 0 };
float spawn_many_y = 0.6f;
#define model_scale 0.0006f         // 0.015f

void set_character_settings(int core_count) {
    if (core_count > 8) {
        spawn_characters3D_count = 256; // 2048;
        spawn_many_radius = 2.0f;
        spawn_many_y = 0.2f;
    } else if (core_count > 6) {
        spawn_characters3D_count = 128;
        spawn_many_radius = 1.4f;
    } else if (core_count > 4) {
        spawn_characters3D_count = 32;
        spawn_many_radius = 0.8f;
    } else {
        spawn_characters3D_count = 8;
    }
    // test single
    #ifdef zoxel_test_character3Ds_single
        spawn_characters3D_count = 1;
        spawn_many_radius = 0.0f;
        spawn_many_offset.x = 8.5f;
        spawn_many_offset.z = 8.5f;
        spawn_many_y = 1.0f;
    #endif
    zoxel_log(" > character settings set\n");
    zoxel_log("     + character spawn count is [%i]\n", spawn_characters3D_count);
}