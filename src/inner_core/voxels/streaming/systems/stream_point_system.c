// Streamer components added to cameras
void StreamPointSystem(ecs_iter_t *it) {
    if (zox_cameras_disable_streaming) return;
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_out(StreamPoint, streamPoints, 3)
    zox_field_out(StreamDirty, streamDirtys, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_o(StreamDirty, streamDirtys, streamDirty)
        if (streamDirty->value != zox_general_state_none) continue;
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_o(StreamPoint, streamPoints, streamPoint)
        const int3 stream_point = real_position_to_chunk_position(position3D->value, default_chunk_size);
        if (int3_equals(stream_point, streamPoint->value)) continue; // no change
        streamPoint->value = stream_point;
        streamDirty->value = zox_general_state_trigger;
    }
} zox_declare_system(StreamPointSystem)
