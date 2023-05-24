#ifndef zoxel_texts
#define zoxel_texts

const double zext_animation_speed = 10.0;
zox_declare_tag(FontStyle)                    //! Contains a bunch of fonts!
zox_declare_tag(Font)                         //! A basic tag for a UI Element.
zox_declare_tag(Zigel)                        //! An individual text character entity.
zox_declare_tag(FontTexture)                  //! A basic tag for a Font TextureData. Generated on a Zigel.
zox_declare_tag(Zext)                         //! Holds all the zigels.
zox_component(ZigelIndex, unsigned char)      //! A character index per zigel.
zox_component(ZextSize, int)                  //! The size of the font in a Zext.
zox_component(ZextDirty, unsigned char)       //! A state event for when Zext is dirty.
zox_component(AnimateZext, double)            //! A Zext that animates
zoxel_byte_component(ZextAlignment)
zox_memory_component(FontData, byte2)         //! An array of points used for generating a font texture
zox_memory_component(ZextData, unsigned char) //! An array of bytes for characters
zox_component(ZextPadding, byte2)
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

zox_begin_module(Texts)
zox_define_tag(Font)
zox_define_tag(Zigel)
zox_define_tag(FontTexture)
zox_define_tag(Zext)
zox_define_tag(FontStyle)
zox_define_component(ZigelIndex)
zox_define_component(ZextSize)
zox_define_component(ZextDirty)
zox_define_component(AnimateZext)
zox_define_component(ZextAlignment)
zox_define_memory_component(FontData)
zox_define_memory_component(ZextData)
zox_define_component(ZextPadding)
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