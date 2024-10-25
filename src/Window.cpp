/*  Window.hpp

The source file for Window.cpp for initalising a window
and the OpenGL context. 

*/

// Include libararies

#include "Window.hpp"

// Window constructor function to initalise window and its properties
Window::Window(int windowWidth, int windowHeight)
	: mWindowWidth{ windowWidth }
	, mWindowHeight{ windowHeight }
{

	// Initialsing SDL
	if (SDL_Init(SDL_INIT_VIDEO < 0))
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL!%s\n", SDL_GetError());
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
			
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); 

	mWindow = SDL_CreateWindow("breakbeat", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL);

	if (mWindow == nullptr)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window!%s\n", SDL_GetError());
		SDL_Quit();
	}

	mWindowClosed = false;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mOpenGLContext = SDL_GL_CreateContext(mWindow);

	if (getOpenGLContext() == nullptr)
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, 
			"OpenGLContext not found! SDL_GL_Error!%s\n", SDL_GetError());

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "glad was not initialized!%s\n", glGetError());
}

SDL_Window*& Window::getWindow()
{
	return mWindow;
}
SDL_GLContext& Window::getOpenGLContext()
{
	return this->mOpenGLContext;
}

int& Window::getWindowWidth()
{
	return this->mWindowWidth;
}
int& Window::getWindowHeight()
{
	return this->mWindowHeight;
}

void Window::setWindowClosedBoolean(bool boolean)
{
	this->mWindowClosed = boolean;
}

bool& Window::getWindowClosedBoolean()
{
	return this->mWindowClosed;
}

SDL_Event& Window::getWindowEvent()
{
	return this->mWindowEvent;
}

void Window::setWindowWidth(int width)
{
	this->mWindowWidth = width;
}
void Window::setWindowHeight(int height)
{
	this->mWindowHeight = height;
}

Window::~Window()
{
	SDL_GL_DeleteContext(mOpenGLContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}


