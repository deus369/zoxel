ecs_entity_t spawn_block_stone(
    ecs_world_t *world,
    const byte index,
    char* name,
    const color block_color
) {
    return spawn_block_voroni(world, index, name, block_color, 80);
}