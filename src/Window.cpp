/*  

Window.cpp

The source file for Window.cpp for initalising a window,
OpenGL states and the OpenGL context for rendering

*/

// Include libararies
#include "Window.hpp"

// Window constructor function to initialize window and its properties
Window::Window() : 
    mLastWindowedHeight { ::MinWindowHeight },
    mLastWindowedWidth { ::MinWindowWidth },
	mIsFullscreen { true },
    mResizeMode { false },
    mFirstTimeWindowed { true }
{
}

void Window::Initialize()
{
    // Initialize SDL
    // Check if the initialization function was sucessful
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        // Log a console error to show that initialization was unsucessfull 
        // Append the actual error that is provided by SDL2 onto the string of the console error
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL! %s\n", SDL_GetError());
    }

    // Query the display's usable display bounds
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
    
    // Create the window and define its position, width and height properties and the type of window it is
    mWindow = SDL_CreateWindow("breakbeat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);

    // If the value return to the mWindow vairable is null then the window failed to be inictiazlaied
    if (mWindow == nullptr)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window! %s\n", SDL_GetError());
        SDL_Quit();
    }

    // Set OpenGL version to 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    	
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

// Function to handle viewport adjustment on window resize
void Window::UpdateViewport(int width, int height)
{
    mWindowWidth = width;
    mWindowHeight = height;
    glViewport(0, 0, width, height);
}

void Window::SetLastWindowedSize(int width, int height)
{
    this->mLastWindowedWidth = width;
    this->mLastWindowedHeight = height;
}

pair<int, int> Window::GetLastWindowedSize() const
{
    return { mLastWindowedWidth, mLastWindowedHeight };
}

void Window::ToggleFullscreen()
{
    mIsFullscreen = !mIsFullscreen;
    mResizeMode = !mResizeMode;

    if (mIsFullscreen)
    {
        // Save current window size before switching to fullscreen
        SDL_GetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);

        // Set fullscreen with native display resolution
        SDL_DisplayMode displayMode;
        if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
        {
            SDL_SetWindowSize(mWindow, displayMode.w, displayMode.h);
            SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
            UpdateViewport(displayMode.w, displayMode.h);
        }
    }
    else
    {
        // Exit fullscreen mode, restore windowed mode size
        SDL_SetWindowFullscreen(mWindow, 0);

        // Retrieve last windowed size
        auto [width, height] = GetLastWindowedSize();
        SDL_SetWindowSize(mWindow, width, height);
        UpdateViewport(width, height);

        // Center the window only the first time it exits fullscreen mode
        if (mFirstTimeWindowed)
        {
            SDL_SetWindowPosition(mWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            mFirstTimeWindowed = false; // Set to false after the first-time centering
        }
    }
}

void Window::HandleWindowResize(SDL_Event& event)
{
    int newWidth = event.window.data1;
    int newHeight = event.window.data2;

    // Clamp the width and height to the minimum values
    if (newWidth < ::MinWindowWidth || newHeight < ::MinWindowHeight)
    {
        newWidth = max(newWidth, ::MinWindowWidth);
        newHeight = max(newHeight, ::MinWindowHeight);

        // Resize the window to the maximum allowed size if too small
        SDL_SetWindowSize(mWindow, newWidth, newHeight);
    }

    // If not in fullscreen, update the last windowed size and viewport
    if (!mIsFullscreen)
    {
        SetLastWindowedSize(newWidth, newHeight);
        UpdateViewport(newWidth, newHeight);
    }
}

Window::~Window()
{
	SDL_GL_DeleteContext(mOpenGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}