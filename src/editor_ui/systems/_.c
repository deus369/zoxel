#include "hierarchy_refresh_system.c"
#include "inspector_element_system.c"

void zox_define_systems_editor(ecs_world_t *world) {
    zox_system(InspectorElementSystem, EcsOnUpdate,
        [in] generic.EntityTarget,
        [in] generic.ComponentTarget,
        [none] InspectorLabel)
    zox_system_1(HierarchyRefreshSystem, zoxp_mainthread,
        [in] transforms2.Position2D,
        [in] elements.core.CanvasPosition,
        [in] elements.core.Layer2D,
        [in] elements.core.Anchor,
        [in] elements2.ListUIMax,
        [in] elements.core.ElementFontSize,
        [in] elements.core.CanvasLink,
        [out] HierarchyUIDirty,
        [out] layouts2.PixelPosition,
        [out] layouts2.PixelSize,
        [out] rendering.TextureSize,
        [out] hierarchys.Children,
        [none] HierarchyUI)
}