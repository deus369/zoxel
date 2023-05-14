#ifndef zoxel_texts
#define zoxel_texts

const double zext_animation_speed = 10.0;
zoxel_declare_tag(FontStyle)                    //! Contains a bunch of fonts!
zoxel_declare_tag(Font)                         //! A basic tag for a UI Element.
zoxel_declare_tag(Zigel)                        //! An individual text character entity.
zoxel_declare_tag(FontTexture)                  //! A basic tag for a Font TextureData. Generated on a Zigel.
zoxel_declare_tag(Zext)                         //! Holds all the zigels.
zoxel_component(ZigelIndex, unsigned char)      //! A character index per zigel.
zoxel_component(ZextSize, int)                  //! The size of the font in a Zext.
zoxel_component(ZextDirty, unsigned char)       //! A state event for when Zext is dirty.
zoxel_component(AnimateZext, double)            //! A Zext that animates
zoxel_byte_component(ZextAlignment)
zoxel_memory_component(FontData, byte2)         //! An array of points used for generating a font texture
zoxel_memory_component(ZextData, unsigned char) //! An array of bytes for characters
zoxel_component(ZextPadding, byte2)
#include "util/default_font.c"
#include "prefabs/font.c"
#include "prefabs/font_style.c"
#include "prefabs/zigel.c"
#include "util/zext_util.c"
#include "prefabs/zext.c"
#include "systems/font_texture_system.c"
#include "systems/zext_update_system.c"
#include "systems/zext_background_update_system.c"
#include "systems/animate_text_system.c"
zox_reset_system(ZextDirtyResetSystem, ZextDirty)

zoxel_begin_module(Texts)
zoxel_define_tag(Font)
zoxel_define_tag(Zigel)
zoxel_define_tag(FontTexture)
zoxel_define_tag(Zext)
zoxel_define_tag(FontStyle)
zoxel_define_component(ZigelIndex)
zoxel_define_component(ZextSize)
zoxel_define_component(ZextDirty)
zoxel_define_component(AnimateZext)
zoxel_define_component(ZextAlignment)
zoxel_define_memory_component(FontData)
zoxel_define_memory_component(ZextData)
zoxel_define_component(ZextPadding)
spawn_font_style_prefab(world);
spawn_font_prefab(world);
spawn_zigel_prefab(world);
spawn_zext_prefab(world);
zox_filter(zextDirtyQuery, [none] Zext, [in] ZextDirty)
zox_filter(generateTextureQuery, [none] FontTexture, [in] GenerateTexture)
// zox_system_1(AnimateTextSystem, EcsOnUpdate, [out] AnimateZext, [out] ZextDirty, [out] ZextData)
zox_system(AnimateTextSystem, EcsOnUpdate, [out] AnimateZext, [out] ZextDirty, [out] ZextData)
#ifdef main_thread_zext_update_system
    zox_system_ctx_1(ZextUpdateSystem, EcsOnUpdate, zextDirtyQuery, [none] Zext, [in] ZextDirty,
        [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] Layer2D, [in] Position2D, [in] PixelSize, [in] ZextAlignment, [out] Children)
#else
    zox_system_ctx(ZextUpdateSystem, EcsOnUpdate, zextDirtyQuery, [none] Zext, [in] ZextDirty,
        [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] Layer2D, [in] Position2D, [in] PixelSize, [in] ZextAlignment, [out] Children)
#endif
zox_system(ZextBackgroundUpdateSystem, EcsOnUpdate, [none] Zext, [in] ZextDirty, [in] ZextData, [in] ZextSize, [in] ZextPadding, [in] CanvasLink, [out] PixelSize, [out] TextureSize, [out] GenerateTexture, [out] MeshVertices2D, [out] MeshDirty)
zox_system_ctx(FontTextureSystem, EcsPreStore, generateTextureQuery, [none] FontTexture, [out] TextureDirty, [out] TextureData, [in] TextureSize, [in] GenerateTexture, [in] ZigelIndex, [in] Color)
zox_define_reset_system(ZextDirtyResetSystem, ZextDirty)
zoxel_end_module(Texts)

// \todo Display a UI Element anchored, with a pixel position.
// \todo Change colour when ray hits a button.

#endif