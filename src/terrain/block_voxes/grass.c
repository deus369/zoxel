ecs_entity_t prefab_world_block_grass;
// todo: make ModelLinks for Blocks and link to LOD number of them
//      ##  Temporary Implementation ##
ecs_entity_t vox_grass_0;
ecs_entity_t vox_grass_1;
ecs_entity_t vox_grass_2;

ecs_entity_t spawn_realm_block_grass(ecs_world_t *world,
    const byte index,
    const color block_color)
{

    vox_grass_0 = spawn_vox_basic(world, prefab_vox, block_vox_depth);
    zox_set_unique_name(vox_grass_0, "block_grass_0")
    zox_set(vox_grass_0, VoxType, { vox_type_rubble })
    zox_set(vox_grass_0, Color, { block_color })
    zox_set(vox_grass_0, GenerateVox, { 1 })
    zox_set(vox_grass_0, RenderLod, { 0 })
    zox_set(vox_grass_0, RubbleHeight, { 30 })
    zox_set(vox_grass_0, RubbleCount, { 9000 })
    vox_grass_1 = spawn_vox_basic(world, prefab_vox, block_vox_depth - 1);
    zox_set_unique_name(vox_grass_1, "block_grass_1")
    zox_set(vox_grass_1, VoxType, { vox_type_rubble })
    zox_set(vox_grass_1, Color, { block_color })
    zox_set(vox_grass_1, GenerateVox, { 1 })
    zox_set(vox_grass_1, RenderLod, { 0 })
    zox_set(vox_grass_1, RubbleHeight, { 15 })
    zox_set(vox_grass_1, RubbleCount, { 1400 })
    vox_grass_2 = spawn_vox_basic(world, prefab_vox, block_vox_depth - 2);
    zox_set_unique_name(vox_grass_2, "block_grass_2")
    zox_set(vox_grass_2, VoxType, { vox_type_rubble })
    zox_set(vox_grass_2, Color, { block_color })
    zox_set(vox_grass_2, GenerateVox, { 1 })
    zox_set(vox_grass_2, RenderLod, { 0 })
    zox_set(vox_grass_2, RubbleHeight, { 7 })
    zox_set(vox_grass_2, RubbleCount, { 200 })

    // use instanced mesh prefab
    SpawnBlock data = {
        .name = "grass",
        .prefab = prefab_block_vox_meta,
        .vox = vox_grass_0,
        .tag = zox_id(BlockVox),
        .index = index,
        .seed = generate_voxel_seed(index),
        .color = generate_random_voxel_color(),
        .model = zox_block_vox,
        .disable_collision = 1,
    };

    // for instancing
    zox_prefab_child_named(prefab_block_vox_instanced, new_world_block)
    zox_set(new_world_block, InstanceLink, { vox_grass_0 })
    zox_set(new_world_block, InstanceLinks, {
        vox_grass_0,
        vox_grass_1,
        vox_grass_2,
        0,
        0,
        0,
        0,
        0
    })
    data.prefab_block_vox = new_world_block;    // links to block meta for spawning
    prefab_world_block_grass = new_world_block;

    // thats all fokes
    process_disabled_block_vox(world, &data, 1);
    return spawn_block_vox_meta(world, &data);
}