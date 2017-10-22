#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

// Pointer to the SDL window
SDL_Window* window = NULL;

// Pointer to the current OpenGL context
SDL_GLContext* context = NULL;

// Initialize SDL and create an OpenGL context
void initSDL() {
    // We only need to initialize the video
    SDL_Init(SDL_INIT_VIDEO);

    // Before creating the context, SDL needs to be configured
    // Set the CORE context profile of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Dedicate some bits to the colors on the window we will be creating (1 byte per color channel => 16+ million colors)
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

    // Use two buffers for drawing to the screen to prevent artifacts
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Optionally, you can set the version of OpenGL that we're going to use
    // In this case we're using the version 4.5
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    // There are many more attributes that you can configure (link: https://wiki.libsdl.org/SDL_GL_SetAttribute)

    // Create the window and store a pointer to it.
    // This creates a 1280 by 720 pixels centered window with an OpenGL context.
    window = SDL_CreateWindow("Exploding chickens", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    // Create the OpenGL context and store a pointer to it.
    context = SDL_GL_CreateContext(window);

    // When double-buffering set the speed to which the buffers are swapped to the speed of the monitor
    SDL_GL_SetSwapInterval(1);
}

void deleteSDL() {
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}

int main(int argc, char** argv) {
    // Initialize
    initSDL();

    // Place to store events that come from the user/application
    SDL_Event ev;

    // Whether or not our loop is still running
    bool running = true;

    // A simple draw loop
    while(running) {
        // There might be more than 1 event per frame, so Poll every SDL event
        while(SDL_PollEvent(&ev)) {
            // If it's this event, close
            if (ev.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    // Clean up
    deleteSDL();
    return 0;
}