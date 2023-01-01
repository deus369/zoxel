// #define zoxel_debug_zext_updates

ecs_entity_t spawn_zext_zigel(ecs_world_t *world, ecs_entity_t zext, int layer,
    int i, int new_children_length, unsigned char zigel_index, int font_size,
    float2 parent_position2D, int2 parent_pixel_size)
{
    int2 zigel_size = (int2) { font_size, font_size };
    float half_size = (zigel_size.x * new_children_length) / 2.0f;
    ecs_entity_t zigel = spawn_zigel(
        world,
        zext,
        zigel_index,
        (int2) { (int) (((float) zigel_size.x * i) - half_size) + zigel_size.x / 2, 0 },
        zigel_size,
        (float2) { 0.5f, 0.5f },
        layer,
        parent_position2D,
        parent_pixel_size);
    return zigel;
}

//! Dynamically updates zext by spawning/destroying zigels and updating remaining.
void spawn_zext_zigels(ecs_world_t *world, ecs_entity_t zext, Children *children, const ZextData *zextData,
    int font_size, unsigned char layer,
    float2 parent_position2D, int2 parent_pixel_size)
{
    ecs_defer_begin(world);
    // int2 zigel_size = (int2) { font_size, font_size };
    int reuse_count = integer_min(children->length, zextData->length);
    #ifdef zoxel_debug_zext_updates
    printf("spawn_zext_zigels :: [%i] -> [%i]; reuse [%i];\n",
        children->length, zextData->length, reuse_count);
    #endif
    // update the reused ones.
    for (int i = 0; i < reuse_count; i++)
    {
        // re set all old zigels, if index changes, regenerate font texture
        ecs_entity_t old_zigel = children->value[i];
        const ZigelIndex *zigelIndex = ecs_get(world, old_zigel, ZigelIndex);
        if (zigelIndex->value != zextData->value[i])
        {
            #ifdef zoxel_debug_zigel_updates
            printf("    - zig updated [%i] [%i] -> [%i]\n",
                i, zigelIndex->value, zextData->value[i]);
            #endif
            ecs_set(world, old_zigel, ZigelIndex, { zextData->value[i] });
            ecs_set(world, old_zigel, GenerateTexture, { 1 });
        }
    }
    if (children->length != zextData->length)
    {
        int old_children_length = children->length;
        ecs_entity_t *old_children = children->value;
        int new_children_length = zextData->length;
        ecs_entity_t *new_children = (ecs_entity_t*) malloc(new_children_length * sizeof(ecs_entity_t));
        for (int i = 0; i < old_children_length; i++)
        {
            new_children[i] = old_children[i];
        }
        // float half_size = (zigel_size.x * new_children_length) / 2.0f;
        if (new_children_length > old_children_length)
        {
            #ifdef zoxel_debug_zext_updates
            printf("    - spawning new_children [%i].\n", (new_children_length - old_children_length));
            #endif
            for (int i = old_children_length; i < new_children_length; i++)
            {
                // convert normal char here to unsigned char!
                new_children[i] = spawn_zext_zigel(world, zext, layer + 1, i, new_children_length,
                    zextData->value[i], font_size, parent_position2D, parent_pixel_size);
                // printf("[%i]: %i\n", i, (int) zextData->value[i]);
            }
        }
        if (new_children_length < old_children_length)
        {
            #ifdef zoxel_debug_zext_updates
            zoxel_log("    - deleting old_children [%i].\n", (old_children_length - new_children_length));
            #endif
            for (int i = new_children_length; i < old_children_length; i++)
            {
                // destroy old zigels, if resizing to less
                ecs_delete(world, old_children[i]);
            }
        }
        if (old_children)
        {
            #ifdef zoxel_debug_zext_updates
            zoxel_log("    - freeing old_children.\n");
            #endif
            free(old_children);
        }
        children->value = new_children;
        children->length = new_children_length;
    }
    #ifdef zoxel_debug_zext_updates
    else
    {
        zoxel_log("    - zext remained the same [%i]\n", zextData->length);
    }
    #endif
    ecs_defer_end(world);
}