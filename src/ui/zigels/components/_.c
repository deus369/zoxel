zox_tag(FontStyle);
zox_tag(TTFFontStyle);
zox_tag(Font);
zox_tag(FontTexture);
zox_tag(Zigel);
zoxc_byte(FontThickness);
zoxc_byte(FontOutlineThickness);
zoxc_byte(ZigelIndex);
zoxc_color(FontFillColor);
zoxc_color(FontOutlineColor);
zoxc_entity(FontLink);
zoxc_arrayd(FontData, byte2)

void define_components_zigels(ecs *world) {
    zox_define_tag(FontStyle);
    zox_define_tag(TTFFontStyle);
    zox_define_tag(Font);
    zox_define_tag(FontTexture);
    zox_define_tag(Zigel);
    zox_define_component_byte(FontThickness);
    zox_define_component_byte(FontOutlineThickness);
    zox_define_component_byte(ZigelIndex);
    zox_define_component_color(FontFillColor);
    zox_define_component_color(FontOutlineColor);
    zox_define_memory_component(FontData);
    zox_define_component_entity(FontLink);
}