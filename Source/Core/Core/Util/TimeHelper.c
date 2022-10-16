// Move functions from SDLUtil.c
#include <time.h>
#include <stdio.h>

const bool isPrintFPS = true;
const double tickRate = 5.0;
double deltaTimeSDL = 0.0;
long framesPerSecond = 0;
double currentTime = 0.0;
double lastTime = 0;
double lastPrinted = tickRate;

void BeginTime()
{
    currentTime = clock() / 1000000.0;
    lastTime = currentTime;
    deltaTimeSDL = 0;
}

void UpdateBeginTime()
{
    // currentTime = SDL_GetTicks();
    currentTime = clock() / 1000000.0;
    deltaTimeSDL = (currentTime - lastTime);
    lastTime = currentTime;
    // printf("deltaTimeSDL: [%f] \n", deltaTimeSDL);
    // double currentTime2 = clock(); // * 1000.0;
    // printf("currentTime: [%f] [%f] \n", currentTime, currentTime2);
}

bool UpdateEndTime()
{
    if (currentTime - lastPrinted >= tickRate)
    {
        lastPrinted = currentTime;
        framesPerSecond /= tickRate;
        if (isPrintFPS)
        {
            printf("DeltaTime [%f]ms - FPS [%ld]\n", (1000.0 * deltaTimeSDL), framesPerSecond);
        }
        framesPerSecond = 0;
        return true;
    }
    framesPerSecond++;
    return false;
}