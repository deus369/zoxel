void clear_mesh(
    MeshIndicies *meshIndicies,
    MeshVertices *meshVertices,
    MeshColorRGBs *meshColorRGBs
) {
    dispose_MeshIndicies(meshIndicies);
    dispose_MeshVertices(meshVertices);
    dispose_MeshColorRGBs(meshColorRGBs);
}

void clear_mesh_uvs(
    MeshIndicies *meshIndicies,
    MeshVertices *meshVertices,
    MeshColorRGBs *meshColorRGBs,
    MeshUVs *meshUVs
) {
    clear_mesh(meshIndicies, meshVertices, meshColorRGBs);
    dispose_MeshUVs(meshUVs);
}