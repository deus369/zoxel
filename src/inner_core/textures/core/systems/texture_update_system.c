//! Not a proper queue yet.
#ifndef maxQueue
#define maxQueue 512
#endif
int queueCount = 0;
int queueTextureIDs[maxQueue];
const Texture* queueTextures[maxQueue];
const TextureSize* queueTextureSizes[maxQueue];

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
    const TextureDirty *textureDirtys = ecs_field(it, TextureDirty, 1);
    const Texture *textures = ecs_field(it, Texture, 2);
    const TextureSize *textureSizes = ecs_field(it, TextureSize, 3);
    const TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 4);
    // printf("TextureUpdateSystem [%i] \n", it->count);
    for (int i = 0; i < it->count; i++)
    {
        const TextureDirty *textureDirty = &textureDirtys[i];
        if (textureDirty->value != 1)
        {
            continue;
        }
        const Texture *texture = &textures[i];
        const TextureSize *textureSize = &textureSizes[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        // printf("Uploaded Texture to GPU: %lu -TextureID [%i] \n", (long int) it->entities[i], textureGPULink->value);
        // add to queue
        queueTextures[queueCount] = texture;
        queueTextureSizes[queueCount] = textureSize;
        queueTextureIDs[queueCount] = textureGPULink->value;
        queueCount++;
        /*glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y,
            0, GL_RGBA, GL_UNSIGNED_BYTE, texture->value);
        glBindTexture(GL_TEXTURE_2D, 0);*/
    }
}
ECS_SYSTEM_DECLARE(TextureUpdateSystem);

//! \todo Make proper queue.
void texture_update_main_thread()
{ 
    if (queueCount == 0)
    {
        return;
    }
    // printf("queueCount: %i \n", queueCount);
    for (int i = queueCount - 1; i >= 0; i--)
    {
        const Texture *texture = queueTextures[i];
        const TextureSize *textureSize = queueTextureSizes[i];
        glBindTexture(GL_TEXTURE_2D, queueTextureIDs[i]);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize->value.x, textureSize->value.y,
            0, GL_RGBA, GL_UNSIGNED_BYTE, texture->value);
        glBindTexture(GL_TEXTURE_2D, 0);
        // printf("Updating TextureID [%i] with texture color.red [%i] \n", queueTextureIDs[i], texture->value[8 + 8 * 16].r);
    }
    queueCount = 0;
}