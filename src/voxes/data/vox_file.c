typedef struct {
  char name[4];
  int chunk_content;
  int chunk_nums;
  int3 xyz;
} vox_file_size;

typedef struct {
  char name[4];
  int chunk_content;
  int chunk_nums;
  unsigned char *voxels;
} vox_file_xyzi;

typedef struct {
  char magic[4];
  int version;
} vox_file_header;

typedef struct {
  char name[4];
  int chunk_content;
  int chunk_nums;
} vox_file_chunk;

typedef struct {
  char name[4];
  int chunk_content;
  int chunk_nums;
  int model_nums;
} vox_file_pack;

typedef struct {
  vox_file_size size;
  vox_file_xyzi xyzi;
} vox_file_chunk_child;

typedef struct {
    char name[4];
    int chunk_content;
    int chunk_nums;
    int values_length;
    color *values;
    color_rgb *values_rgb;
} vox_file_palette;

typedef struct {
    vox_file_header header;
    vox_file_chunk main;
    vox_file_pack pack;
    vox_file_chunk_child *chunks;  // allocate dynamically
    vox_file_palette palette;
} vox_file;
