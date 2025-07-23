ecs_entity_t spawn_model_grass(ecs_world_t* world,
    color c,
    const long int seed)
{
    byte cv = 20;
    srand(seed);
    c.r += -cv + rand() % cv;
    c.g += -cv + rand() % cv;
    c.b += -cv + rand() % cv;
    int big_rubbles = 10000 + rand() % 8000;
    zox_new()
    zox_name("model_grass")
    ModelLods modelLods;
    for (int i = 0; i < 6; i++) {
        if (i > block_vox_depth) {
            modelLods.value[i] = 0;
            continue;
        }
        byte node_depth = block_vox_depth - i;
        byte node_length = powers_of_two[node_depth];
        int place_count = big_rubbles / (pow(i + 1, 2 + i));
        if (place_count == 0) {
            place_count = 1;
        }
        // zox_log("rubble [%i]: [%i]", i, place_count)
        const ecs_entity_t e2 = spawn_vox_basic(world,
            prefab_vox,
            node_depth);
        zox_set_unique_name(e2, "model_lod_grass")
        // default
        zox_set(e2, VoxType, { vox_type_rubble })
        zox_set(e2, GenerateVox, { 1 })
        zox_set(e2, RenderLod, { 0 })
        // important
        zox_set(e2, Seed, { seed })
        zox_set(e2, Color, { c })
        zox_set(e2, RubbleCount, { place_count })
        zox_set(e2, RubbleHeight, { node_length - 1 })
        modelLods.value[i] = e2;
    }
    zox_set_ptr(e, ModelLods, modelLods)
    return e;
}