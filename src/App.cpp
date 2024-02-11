#include "App.h"

#include <SDL.h>

#include <string>
#include <stdexcept>

namespace lazyfoo 
{

App::App( const char *title, const int width, const int height )
    : m_window(nullptr), m_screenSurface(nullptr), m_image(nullptr), 
      m_width(width), m_height(height)
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::string err = std::string("SDL could not initialize! SDL_Error: ") + 
                            std::string(SDL_GetError());        
        throw std::runtime_error( err );
    }

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, m_width, height, SDL_WINDOW_SHOWN);
    if ( !m_window )
    {
        std::string err = std::string("Window could not by created! SDL_Error: ") + 
                            std::string(SDL_GetError());        
        throw std::runtime_error( err );
    }

    m_screenSurface = SDL_GetWindowSurface( m_window );

    if ( !loadMedia() )
    {
        std::string err = std::string("Unable to load image hello_world.bmp! SDL Error: ") + 
                            std::string(SDL_GetError());
        throw std::runtime_error( err );
    }

    SDL_BlitSurface( m_image, nullptr, m_screenSurface, nullptr );

    SDL_UpdateWindowSurface( m_window );
}

App::~App()
{
    SDL_FreeSurface( m_image );
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

bool App::loadMedia()
{
    m_image = SDL_LoadBMP( "../../assets/hello_world.bmp" );
    if ( !m_image )
    {
        return false;
    }

    return true;
}

void App::run()
{
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
}

} // namespace lazyfoo