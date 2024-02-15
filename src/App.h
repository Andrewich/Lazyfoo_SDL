#ifndef APP_H_
#define APP_H_

#include <array>

struct SDL_Window;
struct SDL_Surface;
struct SDL_PixelFormat;

namespace lazyfoo 
{

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

class App {
public:
    App(const char *title, const int width, const int height);
    ~App();
    
    void run();
private:
    SDL_Window*  m_window;
    SDL_Surface* m_screenSurface;
    SDL_Surface* m_image;

    int m_width;
    int m_height;

};

SDL_Surface* loadSurface( const char* path, SDL_PixelFormat* format );
void ShowErrorMessageBox(const char* title, const char* message);

} // namespace lazyfoo

#endif // APP_H_