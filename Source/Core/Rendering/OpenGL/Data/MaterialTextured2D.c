//! A basic x2 building block.
typedef struct
{
    GLuint material;    // link to created material
    // links to locations
    GLint vertexPosition;
    GLint vertexUV;
    GLuint texture;
    GLuint view_matrix;
    GLuint positionX;
    GLuint positionY;
    GLuint angle;
    GLuint scale;
    GLuint brightness;
} MaterialTextured2D;