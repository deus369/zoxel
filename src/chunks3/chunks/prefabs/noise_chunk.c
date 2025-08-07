/*entity spawn_prefab_chunk_noise(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("chunk_noise")
    zox_add_tag(e, NoiseChunk)
    return e;
}

entity spawn_chunk_noise(ecs *world, const entity prefab, const float3 position, const float scale) {
    const entity e = spawn_chunk(world, prefab, position);
    zox_name("chunk_noise")
    zox_set(e, Scale1D, { scale })
    // zox_set(e, AnimateChunk, { (((rand() % 100) / 100.0f) * animating_chunk_speed) });
    return e;
}
*/
