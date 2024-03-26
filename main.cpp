/*
	SDL Playground
*/

#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include <iostream>
#include <string>

#define WINDOW_SCREEN_WIDTH 640
#define WINDOW_SCREEN_HEIGHT 480

/*
	Entry Point
*/

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "(!) Failed to initialize the video subsystem! " << SDL_GetError() << std::endl;
	}

	/*
		Creating a SDL Window!
	*/
	Uint32 windowFlags = 0;
	auto win = SDL_CreateWindow("Minimal SDL3 Application", WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT, windowFlags);

	if (win == nullptr)
	{
		std::cout << "(!) Failed to create the SDL window: " << SDL_GetError() << std::endl;
	}

	/*
		Initialization before the game loop
	*/

	/*
		Game Loop
	*/
	bool isRunning = true;
	while (isRunning)
	{
		// input 
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_QUIT:
				isRunning = false;
				break;
			
			default:
				break;
			}
		}
	}

	SDL_Quit();

	return 0;
}