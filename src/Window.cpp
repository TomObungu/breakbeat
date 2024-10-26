/*  Window.hpp

The source file for Window.cpp for initalising a window
and the OpenGL context. 

*/

// Include libararies
#include "Window.hpp"

// Window constructor function to initialize window and its properties
// Window constructor function to initialize window and its properties
Window::Window(int windowWidth, int windowHeight)
    : mWindowWidth{ windowWidth },
	 mWindowHeight{ windowHeight }
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL! %s\n", SDL_GetError());
    }

    // Query the display's width and height for fullscreen resolution
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not get display mode: %s", SDL_GetError());
    }
    else 
    {
        mWindowWidth = displayMode.w;
        mWindowHeight = displayMode.h;
    }

    // Create the window in fullscreen mode
    mWindow = SDL_CreateWindow("breakbeat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);

	SDL_SetWindowFullscreen(mWindow,SDL_WINDOW_FULLSCREEN);

    if (mWindow == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window! %s\n", SDL_GetError());
        SDL_Quit();
    }

    // Set up OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

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

	mLastWindowedWidth = windowHeight;
	mLastWindowedHeight = windowHeight;
	
    glViewport(0, 0, mWindowWidth, mWindowHeight);
}


// Function to handle viewport adjustment on window resize
void Window::UpdateViewport(int width, int height) {
    mWindowWidth = width;
    mWindowHeight = height;
	SDL_SetWindowSize(mWindow,width,height);
    glViewport(0, 0, width, height);
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

void Window::SetWindowClosedBoolean(bool boolean)
{
	this->mWindowClosed = boolean;
}

bool& Window::GetWindowClosedBoolean()
{
	return this->mWindowClosed;
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

void Window::SetLastWindowedWidth(int width)
{
	this->mLastWindowedWidth = width;
}

int& Window::GetLastWindowedWidth()
{
	return this->mLastWindowedWidth;
}

void Window::SetLastWindowedHeight(int height)
{
	this->mLastWindowedHeight = height;
}

int& Window::GetLastWindowedHeight()
{
	return this->mLastWindowedHeight;
}

Window::~Window()
{
	SDL_GL_DeleteContext(mOpenGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}


