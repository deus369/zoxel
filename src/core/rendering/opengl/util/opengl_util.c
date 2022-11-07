#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// #define DEVBUILD
// first, get working on pc
//  then, move texture updating to the entity system
// texture issues
//  https://www.reddit.com/r/opengl/comments/ydsqkn/textured_square_works_on_pinephone_pro_but_not_pc/
//  https://github.com/edo9300/edopro/issues/151
float3 backgroundColor = { 32.0f / 255.0f, 24.0f / 255.0f, 26.0f / 255.0f };

void OpenGLClear()
{
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);       // Clears the buffer ?
    // glDisable(GL_DEPTH_TEST);
}



/*
Multiple textures:

    https://learnopengl.com/Getting-started/textures

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

*/
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(texture, 0);
    // glEnableTexture(texture);
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(texture, 0);

/*
#ifdef DEVBUILD
    if (!glIsProgram(entityMaterial))
    {
        printf("GL Is not program %i\n", entityMaterial);
        return;
    }
#endif
*/
    // Error 0x500/1280 means GL_INVALID_ENUM