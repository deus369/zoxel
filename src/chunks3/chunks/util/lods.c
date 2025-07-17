/// Map camera distance to a discrete LOD [0…max_lod], or invisible (255) if beyond view.
/// - distance: current chunk’s distance to camera
/// - depth: highest LOD index (e.g. 4 yields LODs 0,1,2,3,4)
/// - near: “near‑field” radius under which LOD 0 applies
/// - far: your global max view distance
static inline byte get_dynamic_lod_from_distance(
    const byte distance,
    const byte depth,
    const byte near,
    const byte far)
{
    // vanish beyond the horizon
    if (distance > far) {
        // zox_log_error(" lod finder out of range: dist [%i] range [%i-%i] depth [%i]", distance, near, far, depth)
        return render_lod_invisible;
    }
    // carve the remaining range (render_distance–init_lod) into max_lod+1 equal slices
    // then find which slice “distance” lives in
    float total_range = (float) (far - near);
    // +1 to avoid divide‑by‑zero when node_depth==0, and to have a small slice at the very end
    int slice = ceil(total_range / ((float) (depth))); //  + 1
    // each increment of i moves us one slice further out
    for (byte i = 0; i <= depth; i++) {
        byte threshold = near + (int)(slice * i); //  + 1
        if (distance <= threshold) {
            if (depth == 5) {
                //found lod: dist [2] range [1-3] depth [5] slice [0.400000] output [3]
                //found lod: dist [3] range [1-3] depth [5] slice [0.400000] output [5]
                // zox_log_error(" found lod: dist [%i] range [%i-%i] depth [%i] slice [%f] output [%i]", distance, near, far, depth, slice, i)
            }
            return i;
        }
    }
    zox_log_error(" fallback lod finder: dist [%i] range [%i-%i] depth [%i] slice [%f]", distance, near, far, depth, slice)
    // fallback (shouldn’t hit, but safe)
    return render_lod_invisible;
}

static inline byte distance_to_terrain_lod(const byte distance) {
    return get_dynamic_lod_from_distance(
        distance,
        terrain_depth,
        terrain_lod_near, //  - 2,
        terrain_lod_far);
}

static inline byte distance_to_lod_vox_block(const byte distance) {
    return get_dynamic_lod_from_distance(
        distance,
        block_vox_depth,
        vox_lod_near,
        terrain_lod_near);
}

static inline byte distance_to_lod_npc(const byte distance) {
    return get_dynamic_lod_from_distance(
        distance,
        character_depth,
        vox_lod_near,
        terrain_lod_near);
}