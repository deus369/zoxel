extern GLuint textureID;
//! Not a proper queue yet.
int queueCount = 0;
int queueTextureID;
const Texture *queueTextures;
const TextureSize *queueTextureSizes;

//! Generate random noise texture.
/**
 * Once main thread is fixed, update to gpu in this system.
 * \todo update to gpu here?
*/
void TextureUpdateSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    const EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 1);
    const Texture *textures = ecs_field(it, Texture, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    for (int i = 0; i < it->count; i++)
    {
        const EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 1)
        {
            continue;
        }
        // printf("Uploaded Texture to GPU: %lu - ID: %i \n", (long int) it->entities[i], textureID);
        const Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        // add to queue
        queueTextures = texture;    // [queueCount]
        queueTextureSizes = textureSize;
        queueTextureID = textureID;
        queueCount++;

        /*glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y,
            0, GL_RGBA, GL_UNSIGNED_BYTE, texture->value);
        glBindTexture(GL_TEXTURE_2D, 0);*/
    }
}
ECS_SYSTEM_DECLARE(TextureUpdateSystem);

//! \todo Make proper queue.
void TextureUpdateSystem2()
{ 
    if (queueCount == 0)
    {
        return;
    }
    // printf("queueCount: %i \n", queueCount);
    for (int i = queueCount - 1; i >= 0; i--)
    {
        const Texture *texture = queueTextures; // [i];
        const TextureSize *textureSize = queueTextureSizes; // [i];
        glBindTexture(GL_TEXTURE_2D, queueTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y,
            0, GL_RGBA, GL_UNSIGNED_BYTE, texture->value);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    queueTextures = NULL;
    queueTextureSizes = NULL;
    queueCount = 0;
}