//! Play music on generates
void MusicGenerateSystem(ecs_iter_t *it)
{
    const GenerateMusic *generateMusics = ecs_field(it, GenerateMusic, 2);
    MusicData *musicDatas = ecs_field(it, MusicData, 3);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateMusic *generateMusic = &generateMusics[i];
        if (generateMusic->value != 1)
        {
            continue;
        }
        MusicData *musicData = &musicDatas[i];
        // reinitialize
        re_initialize_memory_component(musicData, int, 32);
        for (int j = 0; j < musicData->length; j++)
        {
            musicData->value[j] = 30 + rand() % 8;
        }
    }
}
zoxel_declare_system(MusicGenerateSystem);