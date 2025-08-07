#define zox_biome_earthy_forest 0
#define zox_biome_martian 1
#define zox_biome_toxic_swamp 2
#define zox_biome_fungal_alien 3
#define zox_biome_volcanic 4
#define zox_biome_artic_tundra 5
#define zox_biome_radioactive_wasteland 6
#define zox_biome_underground_mushroom 7
#define zox_biome_crystal_valley 8
#define zox_biome_wind_scarred_cliffs 9
#define zox_biome_neon_void 10
#define zox_biome_end 11

typedef struct {
    const char* name;
    float6 dirt;
    float6 grass;
    float6 stone;
    float6 sand;
    float6 obsidian;
    float6 sky;
    float chance;
    float frequency;
} BiomeData;


BiomeData pick_biome(long int seed) {

    const BiomeData bcr_earthy = {
        .name = "Earthy Forest",
        .dirt     = { 25, 35, 50, 70, 30, 50 },   // warm brown
        .grass    = { 90, 140, 60, 90, 50, 70 },  // natural green
        .stone    = { 20, 40, 20, 40, 30, 50 },   // earthy gray-brown
        .sand     = { 40, 50, 30, 50, 60, 80 },   // dry tan sand
        .obsidian = { 0, 30, 20, 40, 10, 30 },    // deep root rock
        .sky      = { 200, 220, 20, 40, 80, 100 }, // peaceful blue
        .chance = 0.28f,
        .frequency = 0.022216,
    };

    const BiomeData bcr_martian = {
        .name = "Martian",
        .dirt     = { 10, 20, 60, 80, 40, 60 },   // dusty red
        .grass    = { 20, 40, 60, 80, 50, 70 },   // rustbrush
        .stone    = { 0, 10, 20, 30, 30, 50 },    // oxidized red stone
        .sand     = { 10, 20, 60, 80, 50, 70 },   // iron sand
        .obsidian = { 0, 20, 30, 50, 10, 30 },    // volcanic plate
        .sky      = { 20, 40, 60, 80, 90, 100 },   // orange-pink smog
        .chance = 0.1f,
        .frequency = 0.03125f,
    };

    const BiomeData bcr_toxic_swamp = {
        .name = "Toxic Swamp",
        .dirt     = { 100, 130, 70, 100, 30, 50 }, // neon dirt
        .grass    = { 60, 100, 90, 100, 50, 80 },  // acid moss
        .stone    = { 90, 110, 20, 40, 30, 50 },   // green-tinged rock
        .sand     = { 70, 90, 80, 100, 40, 60 },   // slime yellow
        .obsidian = { 120, 150, 50, 80, 20, 40 },  // glowing toxic shards
        .sky      = { 80, 110, 70, 100, 50, 80 },   // putrid green clouds
        .chance = 0.1f,
        .frequency = 0.015625f,
    };

    const BiomeData bcr_fungal_alien = {
        .name = "Fungal Alien",
        .dirt     = { 280, 310, 20, 50, 15, 35 },  // purple-gray
        .grass    = { 290, 330, 40, 80, 30, 60 },  // glowing fungus
        .stone    = { 260, 300, 30, 60, 30, 50 },  // dark crystal
        .sand     = { 260, 300, 30, 60, 40, 70 },  // spore dust
        .obsidian = { 270, 310, 40, 60, 20, 40 },  // violet fossil
        .sky      = { 300, 330, 20, 40, 60, 90 },   // fungal fog
        .chance = 0.05f,
        .frequency = 0.017212f,
    };

    const BiomeData bcr_volcanic = {
        .name = "Volcanic",
        .dirt     = { 0, 360, 0, 10, 5, 20 },      // ash
        .grass    = { 0, 30, 10, 20, 10, 30 },     // scorched roots
        .stone    = { 0, 10, 10, 20, 10, 20 },     // lava crust
        .sand     = { 0, 10, 10, 20, 10, 30 },     // black sand
        .obsidian = { 240, 260, 10, 20, 5, 20 },   // blue-black cooled lava
        .sky      = { 10, 30, 80, 100, 70, 100 },   // hell glow
        .chance = 0.15f,
        .frequency = 0.014832f,
    };

    const BiomeData bcr_artic_tundra = {
        .name = "Arctic Tundra Soil",
        .dirt     = { 200, 220, 10, 30, 40, 60 },  // frozen soil
        .grass    = { 180, 220, 20, 40, 60, 80 },  // icy teal moss
        .stone    = { 190, 210, 10, 20, 50, 70 },  // frozen rock
        .sand     = { 190, 210, 10, 30, 70, 90 },  // icy blue sand
        .obsidian = { 210, 240, 10, 20, 20, 40 },  // frozen obsidian
        .sky      = { 190, 230, 10, 30, 90, 100 },  // arctic chill
        .chance = 0.15f,
        .frequency = 0.01125f,
    };

    const BiomeData bcr_radioactive_wasteland = {
        .name = "Radioactive Waste Zone",
        .dirt     = { 90, 110, 80, 100, 40, 60 },  // glowing green
        .grass    = { 70, 110, 90, 100, 70, 90 },  // mutagrass
        .stone    = { 80, 100, 20, 30, 30, 50 },   // irradiated rubble
        .sand     = { 100, 120, 90, 100, 60, 90 }, // toxic crystals
        .obsidian = { 100, 130, 60, 90, 30, 50 },  // nuclear glass
        .sky      = { 100, 140, 90, 100, 80, 100 }, // neon sky
        .chance = 0.04f,
        .frequency = 0.018181f,
    };

    const BiomeData bcr_voidy = {
        .name = "The Void",
        .dirt     = { 0, 360, 0, 0, 0, 10 },       // black void
        .grass    = { 0, 360, 0, 0, 0, 10 },       // black void
        .stone    = { 0, 360, 0, 0, 0, 10 },       // black void
        .sand     = { 0, 360, 0, 0, 0, 10 },       // black void
        .obsidian = { 0, 360, 0, 0, 0, 10 },       // black void
        .sky      = { 240, 260, 0, 0, 0, 5 },       // absolute dark
        .chance = 0.01f,
        .frequency = 0.009999f,
    };

    const BiomeData bcr_underground_mushroom = {
        .name = "Underground Mushroom",
        .dirt     = { 280, 310, 10, 30, 20, 40 },  // dark spore mud
        .grass    = { 290, 310, 30, 60, 40, 60 },  // mycelium carpet
        .stone    = { 250, 270, 20, 40, 30, 50 },  // cavern stone
        .sand     = { 260, 280, 30, 50, 40, 60 },  // spore grit
        .obsidian = { 260, 290, 20, 30, 20, 40 },  // fungal rock
        .sky      = { 290, 320, 10, 20, 10, 30 },  // subterranean gloom
        .chance = 0.05f,
    };

    const BiomeData bcr_crystal_valley = {
        .name = "Crystal Valley",
        .dirt     = { 200, 220, 40, 60, 50, 70 },  // shining soil
        .grass    = { 160, 200, 70, 90, 70, 100 }, // emerald stems
        .stone    = { 180, 200, 60, 80, 50, 70 },  // mineral rock
        .sand     = { 200, 230, 60, 80, 60, 90 },  // sapphire sand
        .obsidian = { 240, 260, 70, 90, 50, 80 },  // amethyst plates
        .sky      = { 210, 230, 80, 100, 90, 100 }, // refracted sky
        .chance = 0.07f,
    };

    const BiomeData bcr_wind_scarred_cliffs = {
        .name = "Wind-Scarred Cliffs",
        .dirt     = { 30, 50, 40, 60, 30, 50 },    // coarse brown
        .grass    = { 70, 90, 50, 70, 40, 60 },    // tough shrubs
        .stone    = { 10, 30, 20, 40, 30, 50 },    // sandstone
        .sand     = { 20, 40, 50, 70, 50, 80 },    // cliff sand
        .obsidian = { 0, 0, 0, 0, 0, 0 },          // none
        .sky      = { 200, 230, 60, 80, 80, 100 }, // dry air blue
        .chance = 0.08f,
    };

    const BiomeData bcr_neon_void = {
        .name = "Neon Void",
        .dirt     = { 300, 330, 90, 100, 80, 100 }, // glowing violet
        .grass    = { 0, 30, 90, 100, 90, 100 },    // burning red
        .stone    = { 240, 270, 80, 100, 70, 90 },  // electric blue
        .sand     = { 60, 90, 100, 100, 90, 100 },  // radioactive yellow
        .obsidian = { 0, 360, 0, 0, 0, 10 },        // void shards
        .sky      = { 280, 310, 90, 100, 100, 100 }, // neon fog
        .chance = 0.02f,
    };
    const BiomeData zox_biomes[] = {
        bcr_earthy,
        bcr_martian,
        bcr_toxic_swamp,
        bcr_fungal_alien,
        bcr_volcanic,
        bcr_artic_tundra,
        bcr_radioactive_wasteland,
        bcr_underground_mushroom,
        bcr_crystal_valley,
        bcr_wind_scarred_cliffs,
        bcr_neon_void,
    };

    srand((unsigned int) seed);
    // byte biome_type = rand() % zox_biome_end;
    float roll = (float)rand() / (float)RAND_MAX;
    float sum = 0.0f;
    for (byte i = 0; i < zox_biome_end; i++) {
        BiomeData biome = zox_biomes[i];
        sum += biome.chance;
        if (roll <= sum) {
            return biome;
        }
    }

    // Fallback to last if float rounding fails
    return zox_biomes[zox_biome_end - 1];
}