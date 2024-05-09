#define check_chunk_lod(dir)\
    (chunkNeighbors->value[direction##_##dir] != 0 &&\
    zox_gett_value(chunkNeighbors->value[direction##_##dir], RenderLod) != \
    get_chunk_division(stream_point, int3##_##dir(chunk_position)))

void StreamPointSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(TerrainLink, terrainLinks, 2)
    zox_field_out(StreamPoint, streamPoints, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(TerrainLink, terrainLinks, terrainLink)
        if (!terrainLink->value) continue;
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_out(StreamPoint, streamPoints, streamPoint)
        const int3 stream_point = get_chunk_position(position3D->value, default_chunk_size);
        if (int3_equals(stream_point, streamPoint->value)) continue; // no change
        streamPoint->value = stream_point;
        zox_set(terrainLink->value, StreamDirty, { 1 })
    }
} zox_declare_system(StreamPointSystem)
