#pragma once
#include "Engine.h"
#include"MenuBar.h"
#include"Mouse.h"
#include <iostream>
#include <vector>
#include <SDL.h>


class DrawArea
{
public:
	DrawArea();
	~DrawArea();

	void Update();

	static std::vector<std::vector<SDL_Point>*> allMouseDraws;

	static bool createNewVector;
	
	
private:
	std::vector<SDL_Point>* singleMouseDraw;
	

	SDL_Texture* drawTexture;
	
	void clearScreen();
	void handleInput();
	void DrawToScreen();
};

