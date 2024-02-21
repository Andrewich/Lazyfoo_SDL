#ifndef APP_H_
#define APP_H_

struct SDL_Window;
struct SDL_Renderer;

namespace lazyfoo 
{

struct Texture;

class App {
public:
    App(const char *title, const int width, const int height);
    ~App();
    
    void run();
private:
    SDL_Window*  m_window;
    SDL_Renderer* m_renderer;
    Texture* m_foo;
    Texture* m_background;

    int m_width;
    int m_height;
};

void ShowErrorMessageBox(const char* title, const char* message);

} // namespace lazyfoo

#endif // APP_H_