/*
	SDL Playground
*/


#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#define WINDOW_SCREEN_WIDTH 640
#define WINDOW_SCREEN_HEIGHT 480


SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string filename);
void blit(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
void keyboardEvent(SDL_KeyboardEvent* e);


typedef struct entity
{
	int x;
	int y;
};


entity player { 0, 0 };

static Mix_Chunk* g_wave = nullptr;

void cleanAudioStuff()
{
	if (g_wave)
	{
		Mix_FreeChunk(g_wave);
		g_wave = nullptr;
	}
}

#define TEST_MIX_CHANNELFINISHED

#ifdef TEST_MIX_CHANNELFINISHED  /* rcg06072001 */

static volatile int channel_is_done = 0;

static void SDLCALL channel_complete_callback(int chan)
{
	//Mix_Chunk* done_chunk = Mix_GetChunk(chan);
	//
	//SDL_Log("We were just alerted that Mixer channel #%d is done.\n", chan);
	//SDL_Log("Channel's chunk pointer is (%p).\n", (void*)done_chunk);
	//SDL_Log(" Which %s correct.\n", (g_wave == done_chunk) ? "is" : "is NOT");
	//
	//channel_is_done = 1;

	std::cout << "(@) channel_complete_callback!!!" << std::endl;
}

#endif


/*
	Entry Point
*/

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

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "(!) Failed to initialize the video subsystem! " << SDL_GetError() << std::endl;
	}

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "(!) Failed to initialize the audio subsystem! " << SDL_GetError() << std::endl;
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


	//Uint32 windowFlags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	Uint32 windowFlags = 0;
	SDL_Window* screen = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT, windowFlags);

	if (screen == nullptr)
	{
		std::cout << "(!) Failed to create the SDL window: " << SDL_GetError() << std::endl;
	}


	/*
		Creating a 2D rendering context for a window.
		
		A renderer hides the details of how we draw into the window.

		This might be using Direct3D, OpenGL, OpenGL ES, or software surfaces behind the scenes, depending on what the system offers;
		your code doesn't change, regardless of what SDL chooses (although you are welcome to force one kind of renderer or another).
		
		If you want to attempt to force sync-to-vblank to reduce tearing, you can use SDL_RENDERER_PRESENTVSYNC instead of zero for the third parameter.
		
		You shouldn't create a window with the SDL_WINDOW_OPENGL flag here. If SDL_CreateRenderer() decides it wants to use OpenGL,
		it'll update the window appropriately for you.

		Follows the enumeration of rendering flags:

			- SDL_RENDERER_SOFTWARE: the renderer is a software fallback
			- SDL_RENDERER_ACCELERATED: the renderer uses hardware acceleration
			- SDL_RENDERER_PRESENTVSYNC: present is synchronized with the refresh rate
			- SDL_RENDERER_TARGETTEXTURE: the renderer supports rendering to texture

	*/

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, rendererFlags);

	if (renderer == nullptr)
	{
		std::cout << "(!) Failed to create the SDL renderer: " << SDL_GetError() << std::endl;
	}

	int numRenderDrivers = SDL_GetNumRenderDrivers();
	std::cout << "> Number of 2D rendering drivers available for the current display: " << numRenderDrivers << std::endl;

	// get info about a specific 2D rendering driver for the current display

	for (int driver = 0; driver < numRenderDrivers; driver++)
	{
		SDL_RendererInfo rendererInfo;
		SDL_GetRenderDriverInfo(driver, &rendererInfo);
		std::cout << "> [" << driver << "] Name of the renderer : " << rendererInfo.name << std::endl;
	}

	// make the scaled rendering look smoother.
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);


	/*
		Initialization before the game loop
	*/

	// loading a simple texture
	//SDL_Texture* myTexture = loadTexture(renderer, "yourimage.png");
	SDL_Texture* myTexture = nullptr;

	bool isRunning = true;
	
	SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	/*
		AUDIO STUFF
	*/
	
	int audioRate = MIX_DEFAULT_FREQUENCY;
	Uint16 audioFormat = MIX_DEFAULT_FORMAT;
	int audioChannels = MIX_DEFAULT_CHANNELS; 

	// initialize SDL_mixer 
	if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, 4096) < 0)
	{
		std::cout << "(!) Failed to MIX open audio: " << SDL_GetError() << std::endl;
	}

	/*
		This function might cover all of an application's needs, but for those that
		need more flexibility, the more powerful version of this function is
		Mix_OpenAudioDevice(). 
	*/

	// find out what the actual audio device parameters are.
	Mix_QuerySpec(&audioRate, &audioFormat, &audioChannels);

	// load a supported audio format into a chunk.
	g_wave = Mix_LoadWAV("youraudio.wav");

	if (g_wave == nullptr)
	{
		std::cout << "(!) Failed to open file: " << SDL_GetError() << std::endl;
	}
	
	Mix_PlayChannel(0, g_wave, 1000);


	/*
		Game Loop
	*/

	while (isRunning)
	{
		// input 
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			
			/*
				keyboard events
			*/

			case SDL_KEYDOWN:
				keyboardEvent(&event.key);
				break;
			
			case SDL_KEYUP:
				keyboardEvent(&event.key);
				break;

			default:
				break;
			}
		}


		/*
			1. SDL_RenderClear() wipes out the existing video framebuffer 
			2. blit() is using SDL_RenderCopy() that moves the texture's contents to the video framebuffer
			3. SDL_RenderPresent() puts it on the screen.
		*/

		// clear the window
		SDL_RenderClear(renderer);

		// blit operation (copying pixels to GPU memory - framebuffer)
		if (myTexture != nullptr)
			blit(renderer, myTexture, player.x, player.y);

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


SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string filename)
{
	int width;
	int height;
	int channel;

	unsigned char* pixels = stbi_load(filename.c_str(), &width, &height, &channel, STBI_rgb_alpha);

	if (pixels == nullptr) {
		std::cout << "(!) Failed to load image file: " << filename;
		return false;
	}

	/*
		SDL2 still has SDL_Surface, but what you want, if possible, is the new SDL_Texture.
		
		Surfaces are always in system RAM now, and are always operated on by the CPU, so we want to get away from there.
		
		SDL2 has a new rendering API. It's meant for use by simple 2D games, but most notably, it's meant to get all that
		software rendering into video RAM and onto the GPU. And even if you just want to use it to get your software renderer's
		work to the screen, it brings some very nice benefits: if possible, it will use OpenGL or Direct3D behind the scenes, which
		means you'll get faster blits, a working Steam Overlay, and scaling for free.

		At this point, your 1.2 game had a bunch of SDL_Surfaces, which it would SDL_BlitSurface() to the screen surface to compose the final framebuffer,
		and eventually SDL_Flip() to the screen. For SDL 2.0, you have a bunch of SDL_Textures, that you will SDL_RenderCopy() to your Renderer to compose
		the final framebuffer, and eventually SDL_RenderPresent() to the screen. It's that simple. If these textures never need modification, you might find
		your framerate has just gone through the roof, too.
	*/

	SDL_Texture* texture;


	/*
		Create a texture for a rendering context.

		SDL_TEXTUREACCESS_STREAMING tells SDL that this texture's contents are going to change frequently.
		SDL_TEXTUREACCESS_STATIC

	*/

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, width, height);

	if (texture == nullptr)
	{
		std::cout << "(!) Failed to create the SDL texture: " << SDL_GetError() << std::endl;
		stbi_image_free(pixels);
		return nullptr;
	}

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);


	/*
		Update the given texture rectangle with new pixel data.
		This will upload your pixels to GPU memory.
	*/

	int ret = SDL_UpdateTexture(texture, nullptr, pixels, width * channel);

	if (ret)
	{
		std::cout << "(!) Failed to update the SDL texture: " << SDL_GetError() << std::endl;
		SDL_DestroyTexture(texture);
		stbi_image_free(pixels);
		texture = nullptr;
	}

	stbi_image_free(pixels);
	return texture;
}


void blit(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
	SDL_Rect finalRect;

	finalRect.x = x;
	finalRect.y = y;
	finalRect.w = 32;
	finalRect.h = 32;

	SDL_QueryTexture(texture, nullptr, nullptr, &finalRect.w, &finalRect.h);

	int ret = SDL_RenderCopy(renderer, texture, nullptr, &finalRect);

	if (ret < 0)
	{
		std::cout << "(!) Failed to copy texture to renderer: " << SDL_GetError() << std::endl;
	}
}


void keyboardEvent(SDL_KeyboardEvent* e)
{
	//if (e->repeat == 0)
	{
		if (e->keysym.scancode == SDL_SCANCODE_UP)
		{
			player.y -= 5;
		}

		if (e->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			player.y += 5;
		}

		if (e->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			player.x -= 5;
		}

		if (e->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			player.x += 5;
		}
	}
}