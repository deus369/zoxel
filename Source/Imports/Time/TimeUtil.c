// Move functions from SDLUtil.c
/*#include <stdio.h>
#include <time.h>

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
    //clock_gettime(CLOCK_REALTIME, &currentTime);
    //printf("CLOCK_REALTIME %f\n", CLOCK_REALTIME);
    const double clocksPerSecond = 1000000.0;
    currentTime = (clock() / clocksPerSecond); //  CLOCKS_PER_SEC);
    deltaTimeSDL = (currentTime - lastTime);
    lastTime = currentTime;
    // deltaTimeSDL = (double) world->deltaTime;
    // printf("deltaTimeSDL: [%f] \n", deltaTimeSDL);

    //deltaTimeSDL = clock.restart().asSeconds();
    //currentTime += deltaTimeSDL;
    // currentTime = SDL_GetTicks();
    // currentTime = (clock() / CLOCKS_PER_SEC) * 1000.0; //  1000000.0;
    // deltaTimeSDL = (currentTime - lastTime);

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
}*/