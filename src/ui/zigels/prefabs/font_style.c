ecs_entity_t spawn_prefab_font_style(ecs_world_t *world, const ecs_entity_t prefab_font) {
    zox_prefab()
    zox_prefab_name("prefab_font_style")
    zox_add_tag(e, FontStyle)
    zox_prefab_add(e, Children)
    zox_prefab_set(e, FontLink, { prefab_font })
    return e;
}

ecs_entity_t spawn_font_style(ecs_world_t *world, const ecs_entity_t prefab) {
    const ecs_entity_t prefab_font = zox_get_value(prefab, FontLink)
    zox_instance(prefab)
    zox_name("font_style")
    zox_get_muter(e, Children, children)
    resize_memory_component(Children, children, ecs_entity_t, font_styles_length)
    for (int i = 0; i < font_styles_length; i++) children->value[i] = 0;
    // lower case
    children->value[1] = spawn_font(world, prefab_font, font_lower_a, font_lower_a_length);
    children->value[2] = spawn_font(world, prefab_font, font_lower_b, font_lower_b_length);
    children->value[3] = spawn_font(world, prefab_font, font_lower_c, font_lower_c_length);
    children->value[4] = spawn_font(world, prefab_font, font_lower_d, font_lower_d_length);
    children->value[5] = spawn_font(world, prefab_font, font_lower_e, font_lower_e_length);
    children->value[6] = spawn_font(world, prefab_font, font_lower_f, font_lower_f_length);
    children->value[7] = spawn_font(world, prefab_font, font_lower_g, font_lower_g_length);
    children->value[8] = spawn_font(world, prefab_font, font_lower_h, font_lower_h_length);
    children->value[9] = spawn_font(world, prefab_font, font_lower_i, font_lower_i_length);
    children->value[10] = spawn_font(world, prefab_font, font_lower_j, font_lower_j_length);
    children->value[11] = spawn_font(world, prefab_font, font_lower_k, font_lower_k_length);
    children->value[12] = spawn_font(world, prefab_font, font_lower_l, font_lower_l_length);
    children->value[13] = spawn_font(world, prefab_font, font_lower_m, font_lower_m_length);
    children->value[14] = spawn_font(world, prefab_font, font_lower_n, font_lower_n_length);
    children->value[15] = spawn_font(world, prefab_font, font_lower_o, font_lower_o_length);
    children->value[16] = spawn_font(world, prefab_font, font_lower_p, font_lower_p_length);
    children->value[17] = spawn_font(world, prefab_font, font_lower_q, font_lower_q_length);
    children->value[18] = spawn_font(world, prefab_font, font_lower_r, font_lower_r_length);
    children->value[19] = spawn_font(world, prefab_font, font_lower_s, font_lower_s_length);
    children->value[20] = spawn_font(world, prefab_font, font_lower_t, font_lower_t_length);
    children->value[21] = spawn_font(world, prefab_font, font_lower_u, font_lower_u_length);
    children->value[22] = spawn_font(world, prefab_font, font_lower_v, font_lower_v_length);
    children->value[23] = spawn_font(world, prefab_font, font_lower_w, font_lower_w_length);
    children->value[24] = spawn_font(world, prefab_font, font_lower_x, font_lower_x_length);
    children->value[25] = spawn_font(world, prefab_font, font_lower_y, font_lower_y_length);
    children->value[26] = spawn_font(world, prefab_font, font_lower_z, font_lower_z_length);
    // upper case
    children->value[27] = spawn_font(world, prefab_font, font_upper_a, font_upper_a_length);
    children->value[28] = spawn_font(world, prefab_font, font_upper_b, font_upper_b_length);
    children->value[29] = spawn_font(world, prefab_font, font_upper_c, font_upper_c_length);
    children->value[30] = spawn_font(world, prefab_font, font_upper_d, font_upper_d_length);
    children->value[31] = spawn_font(world, prefab_font, font_upper_e, font_upper_e_length);
    children->value[32] = spawn_font(world, prefab_font, font_upper_f, font_upper_f_length);
    children->value[33] = spawn_font(world, prefab_font, font_upper_g, font_upper_g_length);
    children->value[34] = spawn_font(world, prefab_font, font_upper_h, font_upper_h_length);
    children->value[35] = spawn_font(world, prefab_font, font_upper_i, font_upper_i_length);
    children->value[36] = spawn_font(world, prefab_font, font_upper_j, font_upper_j_length);
    children->value[37] = spawn_font(world, prefab_font, font_upper_k, font_upper_k_length);
    children->value[38] = spawn_font(world, prefab_font, font_upper_l, font_upper_l_length);
    children->value[39] = spawn_font(world, prefab_font, font_upper_m, font_upper_m_length);
    children->value[40] = spawn_font(world, prefab_font, font_upper_n, font_upper_n_length);
    children->value[41] = spawn_font(world, prefab_font, font_upper_o, font_upper_o_length);
    children->value[42] = spawn_font(world, prefab_font, font_upper_p, font_upper_p_length);
    children->value[43] = spawn_font(world, prefab_font, font_upper_q, font_upper_q_length);
    children->value[44] = spawn_font(world, prefab_font, font_upper_r, font_upper_r_length);
    children->value[45] = spawn_font(world, prefab_font, font_upper_s, font_upper_s_length);
    children->value[46] = spawn_font(world, prefab_font, font_upper_t, font_upper_t_length);
    children->value[47] = spawn_font(world, prefab_font, font_upper_u, font_upper_u_length);
    children->value[48] = spawn_font(world, prefab_font, font_upper_v, font_upper_v_length);
    children->value[49] = spawn_font(world, prefab_font, font_upper_w, font_upper_w_length);
    children->value[50] = spawn_font(world, prefab_font, font_upper_x, font_upper_x_length);
    children->value[51] = spawn_font(world, prefab_font, font_upper_y, font_upper_y_length);
    children->value[52] = spawn_font(world, prefab_font, font_upper_z, font_upper_z_length);
    // numbers
    children->value[60] = spawn_font(world, prefab_font, number_0, number_0_length);
    children->value[61] = spawn_font(world, prefab_font, number_1, number_1_length);
    children->value[62] = spawn_font(world, prefab_font, number_2, number_2_length);
    children->value[63] = spawn_font(world, prefab_font, number_3, number_3_length);
    children->value[64] = spawn_font(world, prefab_font, number_4, number_4_length);
    children->value[65] = spawn_font(world, prefab_font, number_5, number_5_length);
    children->value[66] = spawn_font(world, prefab_font, number_6, number_6_length);
    children->value[67] = spawn_font(world, prefab_font, number_7, number_7_length);
    children->value[68] = spawn_font(world, prefab_font, number_8, number_8_length);
    children->value[69] = spawn_font(world, prefab_font, number_9, number_9_length);
    // special
    children->value[55] = spawn_font(world, prefab_font, font_space, font_space_length);
    children->value[56] = spawn_font(world, prefab_font, font_full_stop, full_stop_length);
    children->value[57] = spawn_font(world, prefab_font, font_comma, font_comma_length);
    children->value[58] = spawn_font(world, prefab_font, font_slash, font_slash_length);
    children->value[59] = spawn_font(world, prefab_font, font_back_slash, font_back_slash_length);
    children->value[70] = spawn_font(world, prefab_font, font_underscore, underscore_length);
    children->value[71] = spawn_font(world, prefab_font, left_square_bracket, left_square_bracket_length);
    children->value[72] = spawn_font(world, prefab_font, right_square_bracket, right_square_bracket_length);
    children->value[73] = spawn_font(world, prefab_font, font_minus, font_minus_length);
    children->value[74] = spawn_font(world, prefab_font, font_plus, font_plus_length);
    children->value[76] = spawn_font(world, prefab_font, font_percentage, font_percentage_length);
    // The Unset ones
    for (int i = 0; i < font_styles_length; i++) if (!children->value[i]) children->value[i] = spawn_font(world, prefab_font, font_question_mark, font_question_mark_length);
    return e;
}
