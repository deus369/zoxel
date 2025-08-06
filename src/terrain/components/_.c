zox_declare_tag(FlatTerrain)
zox_declare_tag(FlatlandChunk)
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_component_entity(TerrainLink)

ecs_entity_t get_linked_terrain(ecs_world_t* world, ecs_entity_t e) {
    return zox_valid(e) && zox_has(e, TerrainLink) ? zox_gett_value(e, TerrainLink) : 0;
}

void define_components_terrain(ecs_world_t *world) {
    zox_define_tag(FlatTerrain)
    zox_define_tag(FlatlandChunk)
    zox_define_tag(TerrainWorld)
    zox_define_tag(TerrainChunk)
    zox_define_tag(ChunkTerrain)
    zox_define_component_entity(TerrainLink)
}