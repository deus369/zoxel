#ifndef zoxel_texts
#define zoxel_texts

// tags
//! A basic tag for a UI Element.
ECS_DECLARE(Font);
//! An individual text character entity.
ECS_DECLARE(Zigel);
//! A basic tag for a Font Texture. Generated on a Zigel.
ECS_DECLARE(FontTexture);
//! Holds all the zigels.
ECS_DECLARE(Zext);
// components
//! An array of points used for generating a font texture.
zoxel_memory_component(FontData, byte2);
//! An array of bytes for characters.
zoxel_memory_component(ZextData, unsigned char);
// prefabs
#include "prefabs/font.c"
#include "prefabs/zigel.c"
#include "prefabs/zext.c"
// systems
#include "systems/font_texture_system.c"

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
    zoxel_memory_component_define(world, FontData);
    zoxel_memory_component_define(world, ZextData);
    add_texture_generation_system(FontTexture, FontTextureSystem);
    spawn_font_prefab(world);
    spawn_zigel_prefab(world);
    spawn_zext_prefab(world);
}
#endif