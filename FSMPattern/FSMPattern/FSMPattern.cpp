// FSMPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "InputHandler.h"
#include <iostream>

#include "Animation.h"
#include "State.h"
#include "Idle.h"
#include "Jumping.h"
#include "Climbing.h"

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//const int SPRITE_SIZE = 510;
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gImageSurface = NULL;

SDL_Rect sourceRect;
SDL_Rect destRect;
InputHandler * handler = new InputHandler();

int m_count = 0;

bool init()
{
	//Initialization flag
	bool success = true;
	//where on the screen it is shown
	sourceRect.x = 20;
	sourceRect.y = -10;
	sourceRect.w = 10;
	sourceRect.y = 10;

	//how big the window is that the sprite is shown in
	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 60;
	destRect.h = 44;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load jpg surface
	gImageSurface = loadSurface("kirby sprite sheet current.png");
	if (gImageSurface == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_FreeSurface(gImageSurface);
	gImageSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}
int main(int argc, char * argv[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			SDL_Event e;
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					handler->handleInput(e, destRect);
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				m_count++;
				if (m_count >= 600)
				{
					destRect.x = destRect.x + 100;
					if (destRect.x > 500)
					{
						destRect.x = 0;
					}
					m_count = 0;
				}

				//Apply the PNG image
				SDL_BlitSurface(gImageSurface, &destRect, gScreenSurface, &sourceRect);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);

			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
 //   //std::cout << "Hello World!\n";
	//Animation fsm; int i = 0;
	//while(true)
	//	if(i == 0)
	//{
	//		fsm.jumping();
	//		this_thread::sleep_for(chrono::microseconds::duration(1000));
	//		//this_thread::sleep_for(chrono::milliseconds dura(1000));
	//		i = 1;
	//	}
	//	else
	//	{
	//		fsm.climbing();
	//		this_thread::sleep_for(chrono::microseconds::duration(1000));
	//		//this_thread::sleep_for(chrono::milliseconds dura(1000));
	//		i = 0;
	//	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
