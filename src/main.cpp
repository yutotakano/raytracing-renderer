/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <json/json.hpp>
#include <argparse/argparse.hpp>
#include <fstream>
#include "scene.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
 * The arguments that the ray tracer takes in.
*/
struct ProgramArgs : public argparse::Args {
    // std::string &anonymous = arg("an anonymous positional string argument");
    std::string &scene_json  = arg("scene", "Path to the JSON file containing the scene description");
    // int &k                 = kwarg("k", "A keyworded integer value");
    // float &alpha           = kwarg("a,alpha", "An optional float value").set_default(0.5f);
    // bool &verbose          = flag("v,verbose", "A flag to toggle verbose");
};

int main(int argc, char *argv[])
{
    // Parse the arguments
    auto args = argparse::parse<ProgramArgs>(argc, argv);

    // Load the JSON file based on the path provided in the arguments
    std::ifstream f(args.scene_json);
    nlohmann::json json_data = nlohmann::json::parse(f);

    std::unique_ptr<Camera> camera_ptr = Camera::fromJson(json_data["camera"]);
    Scene scene = Scene::fromJson(json_data["scene"]);

    // The window we'll be rendering a live preview to
    SDL_Window *window = NULL;

    // The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create window
        window = SDL_CreateWindow(
            "Render Preview",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            camera_ptr->getFilmSize().x(),
            camera_ptr->getFilmSize().y(),
            SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Keep the window open and updating until the user closes it
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }

                // Render the scene
                Uint32 pixel_color = 0xFF000000;
                Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) screenSurface->pixels
                                             + 50 * screenSurface->pitch
                                             + 50 * screenSurface->format->BytesPerPixel);
                *target_pixel = pixel_color;
            }
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
