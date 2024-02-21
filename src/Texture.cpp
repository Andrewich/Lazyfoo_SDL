#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>

#include <stdexcept>
#include <sstream>

namespace lazyfoo
{

Texture::Texture()
    : m_renderer(nullptr), m_texture(nullptr), m_with(0), m_height(0)
{

}

Texture::~Texture()
{
    free();
}

void Texture::loadFromFile(const char* path, SDL_Renderer* renderer)
{
    free();
    m_renderer = renderer;

    SDL_Surface* surface = IMG_Load( path );
    if ( surface == NULL )
    {
        std::stringstream ss;
        ss << "Unable to load image " << path << "! SDL Error: " << SDL_GetError();
        throw std::runtime_error( ss.str() );
    }

    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) );

    m_texture = SDL_CreateTextureFromSurface( m_renderer, surface );
    if ( m_texture == NULL )
    {
        std::stringstream ss;
        ss << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError();
        throw std::runtime_error( ss.str() );
    }

    m_with = surface->w;
    m_height = surface->h;

    SDL_FreeSurface( surface );
}

void Texture::free()
{
    if ( m_texture != nullptr )
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_renderer = nullptr;
        m_with = 0;
        m_height = 0;
    }
}

void Texture::render(int x, int y) const
{
    if ( (m_renderer != nullptr) && (m_texture != nullptr) )
    {
        SDL_Rect dstRect = { x, y, m_with, m_height };
        SDL_RenderCopy( m_renderer, m_texture, nullptr, &dstRect );
    }    
}

} // namespace lazyfoo