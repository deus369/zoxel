//! When ui text updates, spawn/destroy font entities
void ZextUpdateSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        // printf("ZextUpdateSystem: changeQuery didn't change\n");
        return;
    }
    // printf("ZextUpdateSystem: changeQuery changed\n");
    // ecs_query_skip(it); //! Resetting doesn't cause table changes.
    ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 2);
    const ZextData *zextDatas = ecs_field(it, ZextData, 3);
    Children *childrens = ecs_field(it, Children, 4);
    for (int i = 0; i < it->count; i++)
    {
        ZextDirty *zextDirty = &zextDirtys[i];
        if (zextDirty->value != 1)
        {
            // printf("ZextUpdateSystem: ZextDirty is not dirty.\n");
            continue;
        }
        zextDirty->value = 0;
        const ZextData *zextData = &zextDatas[i];
        Children *children = &childrens[i];
        if (children->length != zextData->length)
        {
            printf("Zext was updated! [%i] -> [%i]\n", children->length, zextData->length);
            /*ecs_entity_t *old_children = children->value;
            re_initialize_memory_component_no_free(children, ecs_entity_t, zext->length);
            if (children->length > zext->length)
            {
                for (int j = zext->length; j < children->length; j++)
                {
                    ecs_delete(it->world, children->value[j]);
                }
            }
            else // if (children->length < zext->length)
            {
                for (int j = zext->length; j < children->length; j++)
                {
                    // spawn new
                }
            }
            if (component->length != 0 && component->value)\
            {
                free(component->value);
            }*/
        }
        else
        {
            printf("Zext was updated and text remained the same size!\n");
        }
        //! for all old children, check if zigel index has changed.

        // get font based on zigel index
        /*const ZigelIndex *zigelIndex = &zigelIndexs[i];
        if (zigelIndex->value >= font_styles_length)
        {
            continue;
        }
        ecs_entity_t zigel_font_entity = font_style_children->value[zigelIndex->value];
        const FontData *fontData = ecs_get(world, zigel_font_entity, FontData);
        generate_font_texture(texture, textureSize, fontData);*/
    }
}
ECS_SYSTEM_DECLARE(ZextUpdateSystem);