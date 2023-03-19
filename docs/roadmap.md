# zoxel roadmap

    the timeline of development consisting of milestones

[Back](../readme.md)

-----

## voxels core

- octree subdivisions
- free roam terrain without lag
- LODs of chunks
- camera frustrum culling rendering
- multiple textures on chunks

## blueprints

- basic node ui
- inputs and outputs
- save/load a blueprint
- texture output nodes
- use texture blueprint for voxel textures

## characters

- spawn/destroy characters in chunks
- sub division view distance for character mesh
- physics collision with terrain
- physics/lerp based on view distance
- use blueprint for slime generation
- emoticons above slime heads to express emotions <3 >,<

## stats

- UserStats connecting stats to a entity
- stat types: stat, state, regen, attribute, debuff, buff, etc
- statbars - uis above heads - use instancing for 10k character bars at once
- stat ui - show characters stats in a list

## skills

- UserSkills a user can have skills, a way to interact with the world
- Skill (meta data): a realm contains many skills
- skill target type: target, aoe, channel, wave, summon (creation), movement (teleport)
- resource costs: each skill will cost a state, mana, energy, health, etc
- charge/cast time: a time to prepare the skill after you iniated it
- cooldowns: a skill can have a cooldown, takes time before you can cast again
- animation type: the animation played during the skill use

## quests & dialogues

- using blueprints to make quests
- generate uniqueness based on seeds
- dialogues to follow a pattern but speech can differ, based on seed, npc personality, etc

## statistics & achievements

- record all player actions (data)
- create a set of total game achievements based around this
- slayer achievement (bronze, silver, gold, diamond, dragon, etc) 10, 50, 100, 200, 500 kills