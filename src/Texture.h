#ifndef TEXTURE_H_
#define TEXTURE_H_

struct SDL_Renderer;
struct SDL_Texture;

namespace lazyfoo
{

class Texture
{
public:
    Texture();
    ~Texture();

    void loadFromFile(const char* path, SDL_Renderer* renderer);
    void free();

    void render(int x, int y) const;

    int width() const { return m_with; }
    int height() const { return m_height; }
private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

    int m_with;
    int m_height;
};

} // namespace lazyfoo

#endif // TEXTURE_H_