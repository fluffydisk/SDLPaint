#pragma once

#include <SDL.h>
#include <vector>
#include <map>
#include "Engine.h"



class MenuBar
{
public:
	MenuBar();
	~MenuBar();

	void Update();
	
	static void selectColor();

	static std::vector<std::map<int*, SDL_Rect>>coloursList;

	static SDL_Rect selectedColorTransform;
	static SDL_Rect Background;

private:

	void colourMenu();
	void drawMenus();
	void drawBackground();

};

