#ifndef APP_H_
#define APP_H_

struct SDL_Window;
struct SDL_Texture;
struct SDL_Renderer;

namespace lazyfoo 
{

class App {
public:
    App(const char *title, const int width, const int height);
    ~App();
    
    void run();
private:
    SDL_Window*  m_window;
    SDL_Renderer* m_renderer;    
    SDL_Texture* m_texture;

    int m_width;
    int m_height;

};

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void ShowErrorMessageBox(const char* title, const char* message);

} // namespace lazyfoo

#endif // APP_H_