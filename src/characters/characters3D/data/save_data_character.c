typedef struct {
    float3 position;
    float3 euler;
} SaveDataCharacter;

// Custom hash function for SaveDataCharacter using ulong
ulong compute_character_hash(const SaveDataCharacter* data) {
    ulong hash = 2166136261UL; // FNV-1a 32-bit prime
    const byte* bytes = (const byte*) data;
    for (size_t i = 0; i < sizeof(SaveDataCharacter); ++i) {
        hash ^= bytes[i];
        hash *= 16777619UL; // FNV-1a 32-bit multiplier
    }
    return hash;
}

// Check if the character data needs to be saved
int needs_save(const SaveDataCharacter* current, ulong* prev_hash) {
    ulong new_hash = compute_character_hash(current);
    if (new_hash != *prev_hash) {
        *prev_hash = new_hash; // Update previous hash
        return 1; // Needs saving
    }
    return 0; // No changes
}

// SaveDataCharacter player_save;

create_load_and_save_functions(SaveDataCharacter, player)