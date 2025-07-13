#include "line2D_element_system.c"
#include "line2D_render_system.c"

void define_systems_line2D(ecs_world_t *world) {
    zox_system(Line2DElementSystem, zox_pipelines_pre_render,
        [in] LinePosition2D,
        [in] elements.core.CanvasLink,
        [out] LineData2D,
        [none] Line2D)
    zox_render3D_system(Line2DRenderSystem,
        [in] LineData2D,
        [in] lines.LineThickness,
        [in] colorz.Color,
        [in] elements.core.Layer2D,
        [none] Line2D,
        [none] !ElementLine2D)
    zox_render2D_system(ElementLine2DRenderSystem,
        [in] LineData2D,
        [in] lines.LineThickness,
        [in] colorz.Color,
        [in] elements.core.Layer2D,
        [none] Line2D,
        [none] ElementLine2D)
}