#include <SDL2/SDL.h>
#include <stdio.h>
#include <json/json.hpp>
#include <argparse/argparse.hpp>
#include <fstream>
#include <future>
#include "scene.h"
#include "io/ppm.h"

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

    // Create the camera and scene from the JSON data
    std::shared_ptr<Camera> camera_ptr = Camera::fromJson(json_data["camera"]);
    Scene scene = Scene::fromJson(json_data["scene"]);

    // Create a vector to store the output of the ray tracer.
    // We will pass this to the PPM writer to write to a file, and to the SDL
    // renderer to render to the screen.
    std::vector<Color3f> output(camera_ptr->getFilmSize().x() * camera_ptr->getFilmSize().y());

    // Kick off the ray tracer in a new asynchronous thread
    bool rendering = true;
    std::future<void> renderAsync = std::async(std::launch::async,
        [&rendering, &output, &scene, camera_ptr] {
            // Loop through each pixel in the film
            std::cout << "Rendering..." << std::endl;
            for (int j = 0; j < camera_ptr->getFilmSize().y(); j++) {
                for (int i = 0; i < camera_ptr->getFilmSize().x(); i++) {
                    std::cout << "Pixel " << i << ", " << j << std::endl;

                    // Compute the ray direction for this pixel
                    Ray ray = camera_ptr->generateRay(Point2f(i, j));

                    // Compute the color for this pixel
                    Color3f pixel_color = scene.traceRay(ray, 0, 1000);

                    // Store the color in the output vector
                    output[i + j * camera_ptr->getFilmSize().x()] = Color3f(1, 1, 0);
                }
            }

            rendering = false;
        }
    );

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

            // Fill the surface black
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

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

                // Only re-draw if we're still rendering
                if (rendering)
                {
                    // Display what we have so far to the screen
                    for (int j = 0; j < camera_ptr->getFilmSize().y(); j++) {
                        for (int i = 0; i < camera_ptr->getFilmSize().x(); i++) {
                            Color3f pixel_color = output[i + j * camera_ptr->getFilmSize().x()];

                            // Convert the pixel color to an SDL-compatible format
                            // which is 32-bit RGBA in LSB-order
                            uint32_t pixel_color_int = (uint32_t) (
                                (255 << 24) +
                                (int) (pixel_color.x() * 255) +
                                ((int) (pixel_color.y() * 255) << 8) +
                                ((int) (pixel_color.z() * 255) << 16));

                            // Index into the screen surface's pixel array by bytes
                            uint32_t * const target_pixel = (uint32_t *) (
                                (uint8_t *) screenSurface->pixels +
                                j * screenSurface->pitch +
                                i * screenSurface->format->BytesPerPixel);
                            *target_pixel = pixel_color_int;
                        }
                    }
                    SDL_UpdateWindowSurface(window);
                }
                else
                {
                    // We're done rendering
                }
            }

            // Write to a PPM file when the user closes the window
            PPM::writePPM(output, camera_ptr->getFilmSize(), "output.ppm");
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
