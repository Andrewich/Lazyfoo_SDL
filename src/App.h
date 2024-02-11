#ifndef APP_H_
#define APP_H_

struct SDL_Window;
struct SDL_Surface;

namespace lazyfoo 
{

class App {
public:
    App(const char *title, const int width, const int height);
    ~App();
    
    void run();
private:
    SDL_Window *m_window;
    SDL_Surface *m_screenSurface;
    SDL_Surface *m_image;

    int m_width;
    int m_height;

    bool loadMedia();
};

} // namespace lazyfoo

#endif // APP_H_