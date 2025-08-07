// Streamer components added to cameras
void StreamPointSystem(iter *it) {
    if (zox_cameras_disable_streaming) {
        return;
    }
    // remove these, use only  terrain data
    // const byte depth = terrain_depth;
    // const int3 chunk_dimensions = int3_single(powers_of_two[depth]);
    zox_sys_world();
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(VoxLink)
    zox_sys_out(StreamPoint)
    zox_sys_out(StreamDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(Position3D, position3D)
        zox_sys_o(StreamDirty, streamDirty)
        zox_sys_o(StreamPoint, streamPoint)
        if (streamDirty->value != zox_general_state_none) {
            continue;
        }
        if (!zox_valid(voxLink->value) || !zox_has(voxLink->value, VoxScale) || !zox_has(voxLink->value, NodeDepth)) {
            continue;
        }
        zox_geter_value(voxLink->value, VoxScale, float, terrain_scale);
        zox_geter_value(voxLink->value, NodeDepth, byte, node_depth);

        const int3 stream_point = real_position_to_chunk_position(
            position3D->value,
            powers_of_two[node_depth],
            terrain_scale);
        if (int3_equals(stream_point, streamPoint->value)) {
            continue; // no change
        }
        streamPoint->value = stream_point;
        streamDirty->value = zox_general_state_trigger;
    }
} zox_declare_system(StreamPointSystem)
