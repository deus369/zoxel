#ifndef zoxel_sounds
#define zoxel_sounds

// Tags
ECS_DECLARE(Sound);
// components
//! A sound has an array of bytes.
zoxel_memory_component(SoundData, unsigned char);
//! The length of a sound.
zoxel_component(SoundLength, double);
//! A state event for generating sounds.
zoxel_component(GenerateSound, bool);
//! A state event for playing sounds.
zoxel_component(PlaySound, bool);
// prefabs

// util

// systems

//! Sounds Module.
void SoundsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Sounds);
    ECS_TAG_DEFINE(world, Sound);
    zoxel_memory_component_define(world, SoundData);
    ECS_COMPONENT_DEFINE(world, SoundLength);
    ECS_COMPONENT_DEFINE(world, GenerateSound);
    ECS_COMPONENT_DEFINE(world, PlaySound);
    // systems
    
    // prefabs
    // SpawnSoundPrefab(world);
}
#endif