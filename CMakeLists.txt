cmake_minimum_required(VERSION 3.25)
project(lazyfoo_sdl CXX)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)

add_executable(${PROJECT_NAME} 
                    src/Texture.h
                    src/Texture.cpp
                    src/App.h
                    src/App.cpp
                    src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image-static)
