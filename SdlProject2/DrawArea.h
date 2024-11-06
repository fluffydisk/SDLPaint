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

	static int* pSelectedColor;
	static int brushSize;

	struct singleDraw
	{
		std::vector<SDL_Point> MouseDraws;
		int* SelectedColor;
		int BrushSize;
	};

	static std::vector<singleDraw*> allMouseDraws;

	static bool createNewVector;

	singleDraw* currentDraw;


private:
	
	SDL_Texture* drawTexture;

	void clearScreen();
	void handleInput();
	void DrawToScreen();
};

