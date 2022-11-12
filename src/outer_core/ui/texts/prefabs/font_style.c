ecs_entity_t font_style_prefab;
ecs_entity_t font_style_entity;
const int font_styles_length = 256;

//! meta data for a font character
ecs_entity_t spawn_font_style_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "font_style_prefab");
    zoxel_add_tag(world, e, FontStyle);
    zoxel_add_component(world, e, Children);
    font_style_prefab = e;
    return e;
}

ecs_entity_t spawn_font_style(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, font_style_prefab);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, font_styles_length);
    children->value[0] = spawn_font(world, font_question_mark, font_question_mark_length);
    children->value[27] = spawn_font(world, font_space, font_space_length);
    children->value[1] = spawn_font(world, font_lower_a, font_lower_a_length);
    children->value[2] = spawn_font(world, font_lower_b, font_lower_b_length);
    children->value[3] = spawn_font(world, font_lower_c, font_lower_c_length);
    children->value[4] = spawn_font(world, font_lower_d, font_lower_d_length);
    children->value[5] = spawn_font(world, font_lower_e, font_lower_e_length);
    children->value[6] = spawn_font(world, font_lower_f, font_lower_f_length);
    children->value[7] = spawn_font(world, font_lower_g, font_lower_g_length);
    children->value[8] = spawn_font(world, font_lower_h, font_lower_h_length);
    children->value[9] = spawn_font(world, font_lower_i, font_lower_i_length);
    children->value[10] = spawn_font(world, font_lower_j, font_lower_j_length);
    children->value[11] = spawn_font(world, font_lower_k, font_lower_k_length);
    children->value[12] = spawn_font(world, font_lower_l, font_lower_l_length);
    children->value[13] = spawn_font(world, font_lower_m, font_lower_m_length);
    children->value[14] = spawn_font(world, font_lower_n, font_lower_n_length);
    children->value[15] = spawn_font(world, font_lower_o, font_lower_o_length);
    children->value[16] = spawn_font(world, font_lower_p, font_lower_p_length);
    children->value[17] = spawn_font(world, font_lower_q, font_lower_q_length);
    children->value[18] = spawn_font(world, font_lower_r, font_lower_r_length);
    children->value[19] = spawn_font(world, font_lower_s, font_lower_s_length);
    children->value[20] = spawn_font(world, font_lower_t, font_lower_t_length);
    children->value[21] = spawn_font(world, font_lower_u, font_lower_u_length);
    children->value[22] = spawn_font(world, font_lower_v, font_lower_v_length);
    children->value[23] = spawn_font(world, font_lower_w, font_lower_w_length);
    children->value[24] = spawn_font(world, font_lower_x, font_lower_x_length);
    children->value[25] = spawn_font(world, font_lower_y, font_lower_y_length);
    children->value[26] = spawn_font(world, font_lower_z, font_lower_z_length);
    // children->value[5] = spawn_font(world, font_upper_z, font_upper_z_length);
    for (int i = 28; i < font_styles_length; i++)
    {
        children->value[i] = spawn_font(world, font_question_mark, font_question_mark_length);
    }
    ecs_modified(world, e, Children);
    font_style_entity = e;
    return e;
}

// fontData->value[0] = (byte2) { 128, 50 };
// fontData->value[1] = (byte2) { 128, 200 };
// fontData->value[2] = (byte2) { 50, 128 };
// fontData->value[3] = (byte2) { 200, 128 };
// fontData->value[4] = (byte2) { 50, 50 };
// fontData->value[5] = (byte2) { 200, 200 };