#include <iostream>

#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
    SDL_Window *window = nullptr;
    SDL_Surface *screenSurface = nullptr;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Lazy Foo SDL Tutorial!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if ( !window )
    {
        std::cerr << "Window could not by created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    screenSurface = SDL_GetWindowSurface( window );

    SDL_FillRect( screenSurface, nullptr, SDL_MapRGB( screenSurface->format, 0xFF, 0x00, 0x00) );

    SDL_UpdateWindowSurface( window );

    SDL_Event event;
    bool quit = false;
    while ( !quit )
    {
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
                quit = true;
        }
    }

    SDL_DestroyWindow( window );

    SDL_Quit();

    return 0;
}