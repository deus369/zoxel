void clear_mesh(MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs) {
    clear_memory_component(MeshIndicies, meshIndicies)
    clear_memory_component(MeshVertices, meshVertices)
    clear_memory_component(MeshColorRGBs, meshColorRGBs)
}

void clear_mesh_uvs(MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs, MeshUVs *meshUVs) {
    clear_mesh(meshIndicies, meshVertices, meshColorRGBs);
    clear_memory_component(MeshUVs, meshUVs)
}