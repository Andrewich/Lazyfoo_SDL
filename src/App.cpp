#include "App.h"
#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>

#include <stdexcept>
#include <sstream>

namespace lazyfoo 
{

App::App( const char *title, const int width, const int height )
    : m_window(nullptr), m_renderer(nullptr), 
      m_foo(new Texture()), m_background(new Texture()),
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
    if ( m_window == NULL )
    {
        std::stringstream ss;
        ss << "Window could not by created! SDL_Error: " << SDL_GetError();        
        throw std::runtime_error( ss.str() );
    }

    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
    if ( m_renderer == NULL )
    {
        std::stringstream ss;
        ss << "Renderer could not be created! SDL Error: " << SDL_GetError();        
        throw std::runtime_error( ss.str() );
    }

    SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        std::stringstream ss;
        ss << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();        
        throw std::runtime_error( ss.str() );
    }

    m_foo->loadFromFile( "../../assets/foo.png", m_renderer );
    m_background->loadFromFile( "../../assets/background.png", m_renderer );
}

App::~App()
{
    delete m_background;
    delete m_foo;
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_window );
    IMG_Quit();
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

        SDL_RenderClear( m_renderer );
        m_background->render( 0, 0 );
        m_foo->render( 240, 190 );
        SDL_RenderPresent( m_renderer );
    }
}

void ShowErrorMessageBox(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
}

} // namespace lazyfoo