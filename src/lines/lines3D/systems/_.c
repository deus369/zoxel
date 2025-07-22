#include "line3D_render_system.c"
#include "cube_line_render_system.c"
#include "render_lod_color_system.c"

void define_systems_lines3(ecs_world_t* world) {
    zox_render3D_plus_system(Line3DRenderSystem,
        [in] LineData3D,
        [in] lines.LineThickness,
        [in] colorz.Color,
        [none] Line3D)
    // todo: make overlay layer in render stack
    zox_render3D_plus_system(CubeLineRenderSystem,
        [in] DebugCubeLines,
        [in] CubeLinesThickness,
        [in] colorz.Color,
        [in] transforms3.Position3D,
        [in] transforms3.Rotation3D,
        [in] generic.Bounds3D,
        [none] CubeLines)
    zox_system(RenderLodColorSystem, EcsOnUpdate,
        [in] DebugCubeLines,
        [in] rendering.RenderLod,
        [in] rendering.RenderDisabled,
        [out] colorz.Color,
        [none] CubeLines)

}