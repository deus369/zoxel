zox_tag(Zext);
zox_tag(ZextLabel);
zox_tag(ZextRenderEnabler);
zox_tag(Text2D);
zoxc_byte(ZextDirty);
zoxc_byte(ZextAlignment);
zoxc_byte(TextResolution);
zoxc_byte2(TextPadding);
zoxc_int(TextSize);
zoxc_double(AnimateZext);
zoxc_text(TextData)

void define_components_texts(ecs *world) {
    zox_define_tag(Zext);
    zox_define_tag(ZextLabel);
    zox_define_tag(ZextRenderEnabler);
    zox_define_tag(Text2D);
    zox_define_component_byte(ZextDirty);
    zox_define_component_byte(ZextAlignment);
    zox_define_component_byte(TextResolution);
    zox_define_component_byte2(TextPadding);
    zox_define_component_int(TextSize);
    zox_define_component_double(AnimateZext);
    zox_define_component_zext(TextData);
}