// int characters_count = 0;
const int init_character3D_lod = 1;
const int character3D_lod_dividor = 1;
const unsigned char max_character_division = 0;
int spawn_characters3D_count = 8;
float spawn_many_radius = 0.5f;
float3 spawn_many_offset = float3_zero;
float spawn_many_y = 0.6f;

unsigned char get_character_division_from_camera(unsigned char distance_to_camera) {
    unsigned char division = 255;
    if (distance_to_camera <= init_character3D_lod) division = 0;
    else if (distance_to_camera <= init_character3D_lod + character3D_lod_dividor * 1) division = 1;
    else if (distance_to_camera <= init_character3D_lod + character3D_lod_dividor * 2) division = 2;
    else if (distance_to_camera <= init_character3D_lod + character3D_lod_dividor * 3) division = 3;
    else if (distance_to_camera <= init_character3D_lod + character3D_lod_dividor * 4) division = 4;
    if (max_character_division != 0 && division < max_character_division) division = max_character_division;
    return division;
}

unsigned char get_character_division(int3 chunk_position, int3 camera_position) {
    unsigned char distance_to_camera = get_chunk_division(camera_position, chunk_position);
    return get_character_division_from_camera(distance_to_camera);
}

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
    #ifdef zoxel_debug_settings
        zoxel_log(" > character settings set\n");
        zoxel_log("     + character spawn count is [%i]\n", spawn_characters3D_count);
    #endif
}
