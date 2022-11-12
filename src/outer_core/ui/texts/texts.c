#ifndef zoxel_texts
#define zoxel_texts

// tags
//! Contains a bunch of fonts!
ECS_DECLARE(FontStyle);
//! A basic tag for a UI Element.
ECS_DECLARE(Font);
//! An individual text character entity.
ECS_DECLARE(Zigel);
//! A basic tag for a Font Texture. Generated on a Zigel.
ECS_DECLARE(FontTexture);
//! Holds all the zigels.
ECS_DECLARE(Zext);
//! A Zext that animates.
ECS_DECLARE(AnimatedZext);
// components
//! A character index per zigel.
zoxel_component(ZigelIndex, unsigned char);
//! An array of points used for generating a font texture.
zoxel_memory_component(FontData, byte2);
//! An array of bytes for characters.
zoxel_memory_component(ZextData, unsigned char);
//! A state event for when Zext is dirty.
zoxel_component(ZextDirty, unsigned char);
// util
#include "util/default_font.c"
#include "util/convert_ascii.c"
// prefabs
#include "prefabs/font.c"
#include "prefabs/font_style.c"
#include "prefabs/zigel.c"
#include "prefabs/zext.c"
// systems
#include "systems/font_texture_system.c"
#include "systems/zext_update_system.c"

//! The UI contains ways to interact with 2D objects.
/**
 * \todo Display a UI Element anchored, with a pixel position.
 * \todo Change colour when ray hits a button.
*/
void TextsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Texts);
    ECS_TAG_DEFINE(world, Font);
    ECS_TAG_DEFINE(world, Zigel);
    ECS_TAG_DEFINE(world, FontTexture);
    ECS_TAG_DEFINE(world, Zext);
    ECS_TAG_DEFINE(world, FontStyle);
    ECS_TAG_DEFINE(world, AnimatedZext);
    ECS_COMPONENT_DEFINE(world, ZigelIndex);
    zoxel_memory_component_define(world, FontData);
    zoxel_memory_component_define(world, ZextData);
    ECS_COMPONENT_DEFINE(world, ZextDirty);
    // add_texture_generation_system(FontTexture, FontTextureSystem);
    zoxel_filter(generateTextureQuery, world, [none] FontTexture, [in] GenerateTexture);
    zoxel_system_ctx(world, FontTextureSystem, EcsOnUpdate, generateTextureQuery,
        [none] FontTexture, [out] generic.EntityDirty, [out] Texture, [in] TextureSize, [in] GenerateTexture,
        [in] ZigelIndex);
    zoxel_filter(zextDirtyQuery, world, [none] Zext, [in] ZextDirty);
    zoxel_system_ctx(world, ZextUpdateSystem, EcsOnUpdate, zextDirtyQuery,
        [none] Zext, [out] ZextDirty, [in] ZextData, [out] Children);
    spawn_font_style_prefab(world);
    spawn_font_prefab(world);
    spawn_zigel_prefab(world);
    spawn_zext_prefab(world);
    spawn_font_style(world);
}
#endif