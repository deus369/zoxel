# optimize

- [ ] update vox models to their linked ones in a system over time - instead of in one function (load models)
    - [ ] load only their needed LODs and not the entire model
    - [ ] handle vox block lod changes by loading / unloading at depths

- [ ] generate terrain chunks at different LOD levels - including unloading to keep optimized
    - only render what rendering we need

- [ ] extend terrain LOD size and vox blocks by one chunk so we can see lesser resolution vox blocks


- [ ] don't close same nodes that are vox blocks (only solid and air) - do a check with voxel types
    - [ ] add VoxelNodeGroup byte setting onto voxel meta data
        - pass in array of these settings to the close functions
        - if any voxel in nodes is a vox block, dont group
    - don't close nodes with open end nodes (voxel links)

- [x] Block Spawns huge refactor
    - [x] remove BlockSpawns component as we are no longer using it
    - [x] when updating voxels at end nodes, check for VoxelNodeLink's entity and delete entity on close
    - [x] finish rest of refactor things
    - [x] re do frustum for Block Spawns using delve function
    - [x] put vox cloning on a system frame

- [ ] rename ChunkOctree to VoxelNode
    - [ ] rename the nodes to links - with void* for more general pointer

- [ ] toggle transparent terrain mesh so i can catch minivoxes?

- [ ] toggle key for raycast selection on minivox voxels (mini mode selection or not)
    - so we can test by deleting grass

# later

- [ ] instanced meshes
    - [ ] if non unique, simply load only the mesh required, and not the voxel data
    - [ ] make sure the original models loaded also generate meshes then so we can simply copy it over
    - [ ] we need a seperate system that uses a new GPUMeshLink component that also doesn't delete the gpu part?
        - complicated tho cause when we delete and load gpu resources...! but best not to use same gpu resources for same mesh things

- [x] fix lag between chunks - its very bad atm
    - seems to be directly from block voxes!!!

- [ ] span audio generation to multiple frames... but we should start playing first... we can generate during play! this is hard..

- [ ] record what systems use per frame
    - [ ] in profiler write highest system use in a label

- [ ] GPU (compute) voxel generation in test project
    - [ ] import in simple 2D compute into engine first

    - [ ] GPU instancing draw systems for particles, characters, grass, etc
