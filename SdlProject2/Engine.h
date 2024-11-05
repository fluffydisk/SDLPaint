#pragma once

#include "App.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

class Engine
{
public:
	Engine();
	~Engine();
	static void Start();

	struct COLORS
	{
		static int BLUE[4];
		static int RED[4];
		static int GREEN[4];
		static int BLACK[4];

		static int* ALL_COLOURS[4];
	};

	static SDL_Event e;
	static SDL_Renderer* renderer;
	static SDL_Window* window;
	static TTF_Font* font;

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	
	static int mouseX;
	static int mouseY;
	static bool leftMouse;
	static bool rigtMouse;

	static void UpdateDeltaTime();
	static float deltaTime;
	static float FPS;
	static int frameCount;
	static void UpdateFps();
	
private:
	   
	static Uint32 lastFPSUpdate; 
	static bool init();

	static bool engineShouldEnd;
};

