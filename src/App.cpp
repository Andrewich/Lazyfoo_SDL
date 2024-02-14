#include "App.h"

#include <SDL.h>

#include <stdexcept>
#include <sstream>

namespace lazyfoo 
{

App::App( const char *title, const int width, const int height )
    : m_window(nullptr), m_screenSurface(nullptr), m_image(nullptr),
      m_width(width), m_height(height),
      m_currentSurface(nullptr)
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

    m_screenSurface = SDL_GetWindowSurface( m_window );

    loadMedia();

    m_currentSurface = m_keyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

    SDL_BlitSurface( m_currentSurface, nullptr, m_screenSurface, nullptr );

    SDL_UpdateWindowSurface( m_window );
}

App::~App()
{    
    for(SDL_Surface* s: m_keyPressSurfaces)
    {
        SDL_FreeSurface( s );
    }
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

SDL_Surface* App::loadSurface( const char* path )
{
    m_image = SDL_LoadBMP( path );
    if ( !m_image )
    {
        std::stringstream ss;
        ss << "Unable to load image " << path << "! SDL Error: " << SDL_GetError();        
        throw std::runtime_error( ss.str() );
    }

    return m_image;
}

void App::loadMedia()
{        
    m_keyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "../../assets/press.bmp" );
    m_keyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "../../assets/up.bmp" );    
    m_keyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "../../assets/down.bmp" );    
    m_keyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "../../assets/left.bmp" );    
    m_keyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "../../assets/right.bmp" );        
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

            if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_UP:
                        m_currentSurface = m_keyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                    break;

                    case SDLK_DOWN:
                        m_currentSurface = m_keyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                    break;

                    case SDLK_LEFT:
                        m_currentSurface = m_keyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                    break;

                    case SDLK_RIGHT:
                        m_currentSurface = m_keyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                    break;                    
                }

                SDL_BlitSurface( m_currentSurface, nullptr, m_screenSurface, nullptr );
                SDL_UpdateWindowSurface( m_window );
            }

            if ( event.type == SDL_KEYUP )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_UP:
                    case SDLK_DOWN:
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        m_currentSurface = m_keyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                    break;
                }

                SDL_BlitSurface( m_currentSurface, nullptr, m_screenSurface, nullptr );
                SDL_UpdateWindowSurface( m_window );
            }
        }
    }    
}

void ShowErrorMessageBox(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
}

} // namespace lazyfoo