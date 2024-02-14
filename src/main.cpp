#include "App.h"

#include <string>
#include <stdexcept>

const std::string title{ "Lazy' foo SDL Tutorial" };
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
    try 
    {
        lazyfoo::App app( title.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);

        app.run();
    }
    catch (const std::runtime_error& e)
    {
        lazyfoo::ShowErrorMessageBox("Error", e.what());
    }

    return 0;
}