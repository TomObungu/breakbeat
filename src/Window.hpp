/*  Window.hpp

The header file for Window.cpp which is used for initalising a window
and creating an OpenGL Context witithin the Window using SDL2

*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

// Include 

#include "glad/glad.h"
#include "SDL.h"

#include <memory>
#include <iostream>

using std::cerr;
using std::cout;

class Window
{
public:

	SDL_Window*& getWindow();
	SDL_GLContext& getOpenGLContext();
	SDL_Event& getWindowEvent();
	int& getWindowWidth();
	void setWindowWidth(int);
	int& getWindowHeight();
	void setWindowHeight(int);
	bool& getWindowClosed();
	void setWindowClosed(bool);

	Window(int, int);
	~Window();

private:
	int mWindowWidth;
	int mWindowHeight;
	SDL_Window* mWindow;
	SDL_Event mWindowEvent;
	SDL_GLContext mOpenGLContext;
	bool mWindowClosed;
};

#endif