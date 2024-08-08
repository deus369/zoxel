# optimize

- [ ] Block Spawns huge refactor
    - [ ] remove BlockSpawns component as we are no longer using it
    - [ ] when updating voxels at end nodes, check for VoxelNodeLink's entity and delete entity on close
    - [ ] toggle key for raycast selection on minivox voxels (mini mode selection or not)
        - so we can test by deleting grass
    - [ ] don't close nodes with open end nodes (voxel links)

- [ ] update vox models to their linked ones in a system over time - instead of in one function (load models)
    - [ ] load only their needed LODs and not the entire model

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
