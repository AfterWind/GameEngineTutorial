#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

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
    window = SDL_CreateWindow("Exploding chickens", 80, 80, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    // Create the OpenGL context and store a pointer to it.
    context = SDL_GL_CreateContext(window);

    // When double-buffering set the speed to which the buffers are swapped to the speed of the monitor
    SDL_GL_SetSwapInterval(1);
}

// Initialize OpenGL using glew
void initGL() {
    // Initialize glew
    glewInit();

    // Get errors and check if there are any errors
    // !!! glGetError() resets the error code
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing GL\n");
        // Get the error string and print it in the console
        printf("%s\n", (const char *) gluErrorString(error));
    }

    // Nicely print the version of OpenGL that we're using
    printf("%s\n", glGetString(GL_VERSION));
}

// Remove all allocated resources for our OpenGL context and window and quit SDL.
void deleteSDL() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char** argv) {
    // Initialize
    initSDL();
    initGL();

    // Place to store events that come from the user/application
    SDL_Event ev;

    // Whether or not our loop is still running
    bool running = true;

    // A simple draw loop
    while(running) {
        // What color do we use to clear the window?
        glClearColor(0.5f, 0, 0, 1.0f);

        // Specify that we want to clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // There might be more than 1 event per frame, so Poll every SDL event
        while(SDL_PollEvent(&ev)) {
            // If it's this event, close
            if (ev.type == SDL_QUIT) {
                running = false;
            }
        }

        // Swap back with front buffer
        SDL_GL_SwapWindow(window);
    }

    // Clean up
    deleteSDL();
    return 0;
}