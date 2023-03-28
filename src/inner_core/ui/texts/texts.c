#ifndef zoxel_texts
#define zoxel_texts

const double zext_animation_speed = 10.0;
ecs_entity_t zigel_prefab;
ecs_entity_t zext_prefab;
zoxel_declare_tag(FontStyle)                    //! Contains a bunch of fonts!
zoxel_declare_tag(Font)                         //! A basic tag for a UI Element.
zoxel_declare_tag(Zigel)                        //! An individual text character entity.
zoxel_declare_tag(FontTexture)                  //! A basic tag for a Font Texture. Generated on a Zigel.
zoxel_declare_tag(Zext)                         //! Holds all the zigels.
zoxel_component(ZigelIndex, unsigned char)      //! A character index per zigel.
zoxel_component(ZextSize, int)                  //! The size of the font in a Zext.
zoxel_component(ZextDirty, unsigned char)       //! A state event for when Zext is dirty.
zoxel_component(AnimateZext, double)            //! A Zext that animates.
zoxel_memory_component(FontData, byte2)         //! An array of points used for generating a font texture.
zoxel_memory_component(ZextData, unsigned char) //! An array of bytes for characters.
#include "util/default_font.c"
#include "util/zigel_util.c"
#include "util/zext_util.c"
#include "prefabs/font.c"
#include "prefabs/font_style.c"
#include "prefabs/zigel.c"
#include "prefabs/zext.c"
#include "systems/font_texture_system.c"
#include "systems/zext_update_system.c"
#include "systems/animate_text_system.c"
zoxel_reset_system(ZextDirtyResetSystem, ZextDirty)

void TextsImport(ecs_world_t *world) {
    zoxel_module(Texts)
    zoxel_define_tag(Font)
    zoxel_define_tag(Zigel)
    zoxel_define_tag(FontTexture)
    zoxel_define_tag(Zext)
    zoxel_define_tag(FontStyle)
    zoxel_define_component(ZigelIndex)
    zoxel_define_component(ZextSize)
    zoxel_define_component(ZextDirty)
    zoxel_define_component(AnimateZext)
    zoxel_define_memory_component(FontData)
    zoxel_define_memory_component(ZextData)
    zoxel_filter(zextDirtyQuery, world, [none] Zext, [in] ZextDirty)
    zoxel_filter(generateTextureQuery, world, [none] FontTexture, [in] GenerateTexture)
    zoxel_system_main_thread(world, AnimateTextSystem, EcsOnUpdate, [out] AnimateZext, [out] ZextDirty, [out] ZextData)
    zoxel_system_ctx_main_thread(world, ZextUpdateSystem, EcsOnUpdate, zextDirtyQuery,
        [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] Layer2D,
        [in] Position2D, [in] PixelSize, [out] Children)
    zoxel_system_ctx(world, FontTextureSystem, EcsOnUpdate, generateTextureQuery, [none] FontTexture, [out] TextureDirty,
        [out] Texture, [in] TextureSize, [in] GenerateTexture, [in] ZigelIndex)
    zoxel_reset_system_define(ZextDirtyResetSystem, ZextDirty)
    spawn_font_style_prefab(world);
    spawn_font_prefab(world);
    zigel_prefab = spawn_zigel_prefab(world);
    zext_prefab = spawn_zext_prefab(world);
}
#endif

// \todo Display a UI Element anchored, with a pixel position.
// \todo Change colour when ray hits a button.