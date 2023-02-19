int last_quads;
//! Every noise_animation_speed it makes the update.
void QuadsLabelSystem(ecs_iter_t *it)
{
    unsigned char changed = 0;   //! Skip changes if isn't updated.
    if (last_quads != tri_count)
    {
        last_quads = tri_count;
        changed = 1;
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Tris %i", tri_count);
        const char* text = buffer;
        ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
        ZextData *zextDatas = ecs_field(it, ZextData, 3);
        for (int i = 0; i < it->count; i++)
        {
            ZextDirty *zextDirty = &zextDirtys[i];
            ZextData *zextData = &zextDatas[i];
            zextDirty->value = 1;
            set_zext(zextData, text);
            // printf("    zext data: %i\n", zextData->length);
        }
        // printf("QuadsLabelSystem -: %i [%s]\n", tri_count, buffer);
    }
    if (!changed)
    {
        ecs_query_skip(it);
    }
}
zoxel_declare_system(QuadsLabelSystem)