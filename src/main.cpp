#include <SDL2/SDL.h>
#include <stdio.h>
#include <json/json.hpp>
#include <fstream>
#include <future>
#include <iostream>
#include "io/arguments.h"
#include "scene.h"
#include "io/ppm.h"

int main(int argc, char *argv[])
{
    // Parse the arguments
    Arguments args = Arguments(argc, argv);

    // Load the JSON file based on the path provided in the arguments
    std::ifstream f(args.input_file);
    nlohmann::json json_data = nlohmann::json::parse(f);

    // Create the camera and scene from the JSON data
    std::shared_ptr<Camera> camera_ptr = Camera::fromJson(json_data["camera"]);
    Scene scene = Scene::fromJson(json_data["scene"]);

    // Create a vector to store the output of the ray tracer.
    // We will pass this to the PPM writer to write to a file, and to the SDL
    // renderer to render to the screen.
    std::vector<Color3f> output(camera_ptr->getFilmSize().x() * camera_ptr->getFilmSize().y());

    // Mutex for the output variable as std::vector is not safe for reading
    // while writing from another thread
    std::mutex output_mutex;

    // Kick off the ray tracer in a new asynchronous thread
    std::future<void> renderAsync = std::async(std::launch::async,
        [&args, &output, &output_mutex, &scene, camera_ptr] {
            // Loop through each pixel in the film
            std::cout << "Rendering..." << std::endl;
            for (int j = 0; j < camera_ptr->getFilmSize().y(); j++) {
                for (int i = 0; i < camera_ptr->getFilmSize().x(); i++) {
                    // Compute the ray direction for this pixel
                    Ray ray = camera_ptr->generateRay(Point2f(i, j));

                    // Compute the color for this pixel
                    Color3f pixel_color = scene.traceRay(ray, 0, 1000);

                    // Store the color in the output vector
                    output_mutex.lock();
                    output[i + j * camera_ptr->getFilmSize().x()] = pixel_color;
                    output_mutex.unlock();
                }
            }
            std::cout << "Done rendering!" << std::endl;

            // Write to a PPM file when the user closes the window
            output_mutex.lock();
            PPM::writePPM(output, camera_ptr->getFilmSize(), args.output_file);
            output_mutex.unlock();
        }
    );

    // Whether the live preview has explicitly been disabled
    if (args.no_preview)
    {
        // Block and wait for async thread and exit.
        renderAsync.get();
        return 0;
    }

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
                if (renderAsync.valid())
                {
                    // Acquire the lock on the output vector for this block
                    std::lock_guard<std::mutex> lock(output_mutex);

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
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
