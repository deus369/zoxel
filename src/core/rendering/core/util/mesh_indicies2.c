void clear_mesh(MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs) {
    clear_indicies_component(meshIndicies)
    clear_memory_component(meshVertices)
    clear_memory_component(meshColorRGBs)
}

void clear_mesh_uvs(MeshIndicies *meshIndicies, MeshVertices *meshVertices, MeshColorRGBs *meshColorRGBs, MeshUVs *meshUVs) {
    clear_mesh(meshIndicies, meshVertices, meshColorRGBs);
    clear_memory_component(meshUVs)
}