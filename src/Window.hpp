/*  

Window.hpp

The header file for Window.cpp which is used for initalising a window
and creating an OpenGL Context within the window using SDL2 and glad

*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

// Include external libaries for window initialisation

#include "glad/glad.h"
#include "SDL.h"

namespace
{
	inline constexpr int WindowWidth { 800 } ;
	inline constexpr int WindowHeight { 600 };
}

class Window
{
public:

	//  Getters and setters
	SDL_Window*& GetWindow();
	SDL_GLContext& GetOpenGLContext();
	SDL_Event& GetWindowEvent();
	int& GetWindowWidth();
	bool& GetWindowClosedBoolean();
	void SetWindowClosedBoolean(bool);
	void SetWindowWidth(int);
	int& GetWindowHeight();
	void SetWindowHeight(int);
	// Window constructor containing the width and the height of the window as parameters

	Window();
	~Window();

private:

	// Window class memembers for window properties
	int mWindowWidth;
	int mWindowHeight;
	SDL_Window* mWindow;
	SDL_Event mWindowEvent;
	bool mWindowClosedBoolean;

	// OpenGL context 
	SDL_GLContext mOpenGLContext;
};

#endif