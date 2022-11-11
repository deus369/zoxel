ecs_entity_t font_prefab;
ecs_entity_t font_entity;

//! meta data for a font character
ecs_entity_t spawn_font_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "font_prefab");
    zoxel_add_tag(world, e, Font);
    zoxel_add_component(world, e, FontData);
    font_prefab = e;
    return e;
}

const unsigned char font_question_mark_length = 9 * 2;
const byte2 font_question_mark[] =
{
    { 3, 13 }, { 13, 13 },  // top line
    { 3, 13 }, { 3, 9 },
    { 3, 9 }, { 5, 9 },
    { 13, 13 }, { 13, 7 },
    { 13, 7 }, { 7, 7 }, // right middle to middle
    { 7, 7 }, { 7, 5 }, // middle to down
    { 6, 3 }, { 8, 3 }, // dot
    { 6, 2 }, { 8, 2 }
};

const int font_left_side = 2;
const int font_right_side = 13;
const int font_bottom_side = 2;
const int font_top_side = 13;
const unsigned char font_upper_z_length = 3 * 2;
const byte2 upper_z[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side - 1 },  // top line
    { font_right_side, font_top_side - 1 }, { font_left_side, font_bottom_side + 1 },
    { font_left_side, font_bottom_side + 1 }, { font_right_side, font_bottom_side }
};

ecs_entity_t spawn_font(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, font_prefab);
    FontData *fontData = ecs_get_mut(world, e, FontData);
    int font_length = font_upper_z_length;
    initialize_memory_component(fontData, byte2, font_length);
    for (int i = 0; i < font_length; i++)
    {
        fontData->value[i] = byte2_multiply_int(upper_z[i], 16);
    }
    ecs_modified(world, e, FontData);
    font_entity = e;
    return e;
}

// fontData->value[0] = (byte2) { 128, 50 };
// fontData->value[1] = (byte2) { 128, 200 };
// fontData->value[2] = (byte2) { 50, 128 };
// fontData->value[3] = (byte2) { 200, 128 };
// fontData->value[4] = (byte2) { 50, 50 };
// fontData->value[5] = (byte2) { 200, 200 };