/*  

Window.cpp

The source file for Window.cpp for initalising a window,
OpenGL states and the OpenGL context for rendering

*/

// Include libararies
#include "Window.hpp"

// Window constructor function to initialize window and its properties
Window::Window() :
 mWindowWidth { ::WindowWidth },
 mWindowHeight { ::WindowHeight }
{
    // Initialize SDL
    // Check if the initialization function was sucessful
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        // Log a console error to show that initialization was unsucessfull 
        // Append the actual error that is provided by SDL2 onto the string of the console error
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL! %s\n", SDL_GetError());
    }
    
    // Create the window and define its position, width and height properties and the type of window it is
    mWindow = SDL_CreateWindow("breakbeat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL);

    // If the value return to the mWindow vairable is null then the window failed to be initiazlaied
    if (mWindow == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window! %s\n", SDL_GetError());
        SDL_Quit();
    }

    // Set OpenGL version to 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Set up OpenGL attributes for anti-aliasing
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
			
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    // Create the OpenGL context
    mOpenGLContext = SDL_GL_CreateContext(mWindow);
    if (mOpenGLContext == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL context! %s\n", SDL_GetError());
    }

    // Load OpenGL functions
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize glad! %s\n", glGetError());
    }
}


SDL_Window*& Window::GetWindow()
{
	return mWindow;
}
SDL_GLContext& Window::GetOpenGLContext()
{
	return this->mOpenGLContext;
}

int& Window::GetWindowWidth()
{
	return this->mWindowWidth;
}
int& Window::GetWindowHeight()
{
	return this->mWindowHeight;
}

SDL_Event& Window::GetWindowEvent()
{
	return this->mWindowEvent;
}

void Window::SetWindowWidth(int width)
{
	this->mWindowWidth = width;
}
void Window::SetWindowHeight(int height)
{
	this->mWindowHeight = height;
}

void Window::SetWindowClosedBoolean(bool boolean)
{
	this->mWindowClosedBoolean = boolean;
}

bool& Window::GetWindowClosedBoolean()
{
	return this->mWindowClosedBoolean;
}

Window::~Window()
{
	SDL_GL_DeleteContext(mOpenGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}