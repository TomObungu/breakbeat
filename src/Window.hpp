/*  Window.hpp

The header file for Window.cpp which is used for initalising a window
and creating an OpenGL Context witithin the Window using SDL2

*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

// Include libaries for window initialisation

#include "glad/glad.h"
#include "SDL.h"

// Window class, will be used as association witihin the main breakbeat.cpp file

class Window
{
public:

	//  Getters and setters
	SDL_Window*& GetWindow();
	SDL_GLContext& GetOpenGLContext();
	SDL_Event& GetWindowEvent();
	int& GetWindowWidth();
	void SetWindowWidth(int);
	int& GetWindowHeight();
	void SetWindowHeight(int);
	void SetLastWindowedWidth(int);
	int& GetLastWindowedWidth();
	void SetLastWindowedHeight(int);
	int& GetLastWindowedHeight();
	bool& GetWindowClosedBoolean();
	void SetWindowClosedBoolean(bool);
	void UpdateViewport(int width, int height);

	// Window constructor containing the width and the height of the window as parameters

	Window(int, int);
	~Window();

private:

	// Window class memembers for window properties
	int mWindowWidth;
	int mWindowHeight;
	int mLastWindowedWidth;
	int mLastWindowedHeight;
	SDL_Window* mWindow;
	SDL_Event mWindowEvent;

	// OpenGL context 
	SDL_GLContext mOpenGLContext;

	// Boolean value to check if window is closed
	bool mWindowClosed;
};

#endif