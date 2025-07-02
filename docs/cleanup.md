// dump any notes from source in here

// todo: destroy block voxes if removed from chunk, check hashes / current block voxes
// todo: also check if hashes exist but voxel type has changed!

// this should only trigger if voxel updates is air, or solid (vox blocks should not close same nodes)
// todo: if voxel type == CanBlockGroup
// todo: only do this on node updated! and it's parent nodes
// should be, BlockVoxesDirty
// if block meta is minivox or vox entity:
// todo: just check for spawned entity, spawn either minivox or block entity here

// should we just set nodes here?
// - note: it may need to open or close a node
//      - if solid, and its in air of higher size, now need open node
//      - if air inside solid, solid is higher, now need open node
//      - if air and only one solid, and now all air, need close node