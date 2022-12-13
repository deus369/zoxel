#include <stdio.h>
#include <stdlib.h>

/* Define a struct to store the voxel data. */
typedef struct Voxel {
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned char color;
} Voxel;

/* Define a struct to store the vox file data. */
typedef struct VoxFile {
  int numVoxels;
  Voxel* voxels;
} VoxFile;

void read_vox(const char* filename)
{
    // char* file_path
    // Open the vox file for reading
    FILE *vox_file = fopen("vox_file.vox", "rb");

    // Check if the file was opened successfully
    if (vox_file == NULL)
    {
        // Print an error message and exit if the file could not be opened
        printf("Error: Could not open vox file!\n");
        exit(1);
    }


    // Read the magic number from the file
    fread(magic, sizeof(char), 4, vox_file);

    // Check if the magic number is correct
    if (strcmp(magic, "VOX ") != 0)
    {
        // Print an error message and exit if the magic number is invalid
        printf("Error: Invalid vox file!\n");
        exit(1);
    }

    // Read the version number from the file
    fread(&version, sizeof(int), 1, vox_file);

    // Check if the version number is supported
    if (version != 150)
    {
        // Print an error message and exit if the version is not supported
        printf("Error: Unsupported vox file version!\n");
        exit(1);
    }

    // Read the voxel data from the file
    // ...

    // Close the vox file when we're done
    fclose(vox_file);
}