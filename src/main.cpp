#include "App.h"

#include <string>

const std::string title{ "Lazy' foo SDL Tutorial" };
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
    lazyfoo::App app( title.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);

    app.run();

    return 0;
}