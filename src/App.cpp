#include "App.h"

#include <SDL.h>
#include <SDL_image.h>

#include <stdexcept>
#include <sstream>

namespace lazyfoo 
{

App::App( const char *title, const int width, const int height )
    : m_window(nullptr), m_screenSurface(nullptr),
      m_width(width), m_height(height)
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::stringstream ss;
        ss << "SDL could not initialize! SDL_Error: " << SDL_GetError();        
        throw std::runtime_error( ss.str() );
    }

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, m_width, height, SDL_WINDOW_SHOWN);
    if ( !m_window )
    {
        std::stringstream ss;
        ss << "Window could not by created! SDL_Error: " << SDL_GetError();        
        throw std::runtime_error( ss.str() );
    }

    if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        std::stringstream ss;
        ss << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();        
        throw std::runtime_error( ss.str() );
    }

    m_screenSurface = SDL_GetWindowSurface( m_window );    

    m_image = loadSurface( "../../assets/loaded.png", m_screenSurface->format );
}

App::~App()
{    
    SDL_FreeSurface( m_image );    
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

void App::run()
{
    SDL_Event event;
    bool quit = false;
    while ( !quit )
    {
        while ( SDL_PollEvent( &event ) )
        {
            if ( (event.type == SDL_QUIT) || ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) )
                quit = true;
        }

            //Apply the image stretched
            SDL_Rect stretchRect;
            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.w = m_width;
            stretchRect.h = m_height;
            SDL_BlitScaled( m_image, NULL, m_screenSurface, &stretchRect );    

            SDL_UpdateWindowSurface( m_window );
    }    
}

SDL_Surface* loadSurface( const char* path, SDL_PixelFormat* format )
{
    SDL_Surface* raw_image = IMG_Load( path );
    if ( !raw_image )
    {
        std::stringstream ss;
        ss << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError();        
        throw std::runtime_error( ss.str() );
    }

    SDL_Surface* optimized_surface = SDL_ConvertSurface( raw_image, format, 0 );
    SDL_FreeSurface( raw_image );
    if ( !optimized_surface )
    {        
        std::stringstream ss;
        ss << "Unable to optimize image " << path << "! SDL Error: " << SDL_GetError();        
        throw std::runtime_error( ss.str() );
    }

    return optimized_surface;
}

void ShowErrorMessageBox(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
}

} // namespace lazyfoo