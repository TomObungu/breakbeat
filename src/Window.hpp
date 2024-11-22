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
#include <utility>
#include <algorithm>

// Constants to define the smallest possible window resolution
namespace
{
    inline constexpr int MinWindowWidth  { 640 };
    inline constexpr int MinWindowHeight { 480 };
}

using std::pair;
using std::max;

class Window
{
public:

	//  Getters and setters
	void Initialize();
	SDL_Window*& GetWindow();
	SDL_GLContext& GetOpenGLContext();
	SDL_Event& GetWindowEvent();
	int& GetWindowWidth();
	void SetLastWindowedSize(int, int);
	pair<int, int> GetLastWindowedSize() const;
	bool& GetWindowClosedBoolean();
	void SetWindowClosedBoolean(bool);
	void SetWindowWidth(int);
	int& GetWindowHeight();
	void SetWindowHeight(int);
	void HandleWindowResize(SDL_Event&);
	void UpdateViewport(int width, int height);
	void ToggleFullscreen();

	// Window constructor containing the width and the height of the window as parameters

	Window();
	~Window();

private:

	// Window class memembers for window properties
	int mWindowWidth;
	int mWindowHeight;
	int mLastWindowedWidth;
	int mLastWindowedHeight;
	SDL_Window* mWindow;
	SDL_Event mWindowEvent;
	bool mWindowClosedBoolean;

	// Boolean value to check if window is closed
	bool mWindowClosed;
	bool mIsFullscreen;
    bool mResizeMode;
    bool mFirstTimeWindowed;

	// OpenGL context 
	SDL_GLContext mOpenGLContext;
};

#endif