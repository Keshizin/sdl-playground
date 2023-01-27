/*
	SDL Playground
*/


#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	/*
		Initialize the SDL library.
		The file I/O (for example: SDL_RWFromFile) and threading (SDL_CreateThread) subsystems are initialized by default.

		Message boxes (SDL_ShowSimpleMessageBox) and Logging (such as SDL_Log) work without initializing.

		You must specifically initialize other subsystems if you use them in your application.

			- SDL_INIT_TIMER: timer subsystem
			- SDL_INIT_AUDIO : audio subsystem
			- SDL_INIT_VIDEO: video subsystem; automatically initializes the events subsystem
			- SDL_INIT_JOYSTICK : joystick subsystem; automatically initializes the events subsystem
			- SDL_INIT_HAPTIC: haptic(force feedback) subsystem
			- SDL_INIT_GAMECONTROLLER : controller subsystem; automatically initializes the joystick subsystem
			- SDL_INIT_EVENTS: events subsystem
			- SDL_INIT_EVERYTHING : all of the above subsystems
			- SDL_INIT_NOPARACHUTE: compatibility; this flag is ignored
	*/

	int errorCode = SDL_Init(SDL_INIT_VIDEO);

	if (errorCode != 0)
	{
		std::cout << "(!) Failed to initialize the video subsystem! Error code: " << errorCode << " - " << SDL_GetError() << std::endl;
	}


	/*
		Create a window with the specified position, dimensions, and flags.

		Follows the list fo window flags:

			- SDL_WINDOW_FULLSCREEN: fullscreen window
			- SDL_WINDOW_FULLSCREEN_DESKTOP: fullscreen window at the current desktop resolution
			- SDL_WINDOW_OPENGL: window usable with OpenGL context
			- SDL_WINDOW_VULKAN: window usable with a Vulkan instance
			- SDL_WINDOW_SHOWN: window is visible
			- SDL_WINDOW_HIDDEN: window is not visible
			- SDL_WINDOW_BORDERLESS: no window decoration
			- SDL_WINDOW_RESIZABLE: window can be resized
			- SDL_WINDOW_MINIMIZED: window is minimized
			- SDL_WINDOW_MAXIMIZED: window is maximized
			- SDL_WINDOW_INPUT_GRABBED: window has grabbed input focus
			- SDL_WINDOW_INPUT_FOCUS: window has input focus
			- SDL_WINDOW_MOUSE_FOCUS: window has mouse focus
			- SDL_WINDOW_FOREIGN: window not created by SDL
			- SDL_WINDOW_ALLOW_HIGHDPI: window should be created in high-DPI mode if supported (>= SDL 2.0.1)
			- SDL_WINDOW_MOUSE_CAPTURE: window has mouse captured (unrelated to INPUT_GRABBED, >= SDL 2.0.4)
			- SDL_WINDOW_ALWAYS_ON_TOP: window should always be above others (X11 only, >= SDL 2.0.5)
			- SDL_WINDOW_SKIP_TASKBAR: window should not be added to the taskbar (X11 only, >= SDL 2.0.5)
			- SDL_WINDOW_UTILITY: window should be treated as a utility window (X11 only, >= SDL 2.0.5)
			- SDL_WINDOW_TOOLTIP: window should be treated as a tooltip (X11 only, >= SDL 2.0.5)
			- SDL_WINDOW_POPUP_MENU: window should be treated as a popup menu (X11 only, >= SDL 2.0.5)

		The SDL_WINDOW_OPENGL flag prepares your window for use with OpenGL, but you will still need to create an OpenGL context
		using SDL_GL_CreateContext() after window creation, before calling any OpenGL functions.
	*/

	Uint32 windowFlags = 0;
	SDL_Window* screen = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, windowFlags);

	if (screen == nullptr)
	{
		std::cout << "(!) Failed to create the SDL window: " << SDL_GetError() << std::endl;
	}


	/*
		Creating a 2D rendering context for a window.

		Follows the enumeration of rendering flags:

			- SDL_RENDERER_SOFTWARE: the renderer is a software fallback
			- SDL_RENDERER_ACCELERATED: the renderer uses hardware acceleration
			- SDL_RENDERER_PRESENTVSYNC: present is synchronized with the refresh rate
			- SDL_RENDERER_TARGETTEXTURE: the renderer supports rendering to texture

	*/

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, rendererFlags);

	if (renderer == nullptr)
	{
		std::cout << "(!) Failed to create the SDL renderer: " << SDL_GetError() << std::endl;
	}

	std::cout << "> Number of 2D rendering drivers available for the current display: " << SDL_GetNumRenderDrivers << std::endl;

	SDL_RendererInfo rendererInfo;
	//SDL_GetRenderDriverInfo(2, &rendererInfo);


	/*
		Game Loop
	*/

	bool isRunning = true;

	while (isRunning)
	{
		// clear the window
		SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
		SDL_RenderClear(renderer);
		

		// input 
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			default:
				break;
			}
		}


		// render
		SDL_RenderPresent(renderer);

		// governing the frame time
		SDL_Delay(16);
	}


	/*
		Destroy the rendering context for a window and free associated textures.
	*/

	SDL_DestroyRenderer(renderer);


	/*
		Shut down all initialized SDL subsystems.

		Subsystem initialization is ref-counted, you must call SDL_QuitSubSystem() for each SDL_InitSubSystem() to correctly
		shutdown a subsystem manually (or call SDL_Quit() to force shutdown).

		You still need to call SDL_Quit() even if you close all open subsystems with SDL_QuitSubSystem().
	*/

	SDL_Quit();

	return 0;
}