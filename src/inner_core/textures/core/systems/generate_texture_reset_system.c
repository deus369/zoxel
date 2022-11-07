//! Resets EntityDirty after one frame.
/**
 * \todo MakeReset system a system_macro.
*/
void GenerateTextureResetSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    // printf("GenerateTexture was Dirty!\n");
    ecs_query_skip(it); //! Resetting doesn't cause table changes.
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 1);
    for (int i = 0; i < it->count; i++)
    {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value == 1)
        {
            generateTexture->value = 0;
            // printf("GenerateTexture Reseting!\n");
        }
    }
}
ECS_SYSTEM_DECLARE(GenerateTextureResetSystem);