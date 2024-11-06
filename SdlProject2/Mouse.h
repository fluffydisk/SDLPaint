#pragma once

#include "MenuBar.h"
#include "DrawArea.h"

class Mouse
{
public:
	Mouse();
	~Mouse();

	static void Update();
	static bool ableToDraw;
	static bool erase;
	static void INIT();


private:
	//static enum MouseCursorMode{ DRAWING_AREA_DRAW, DRAWING_AREA_ERASE, MENU_BAR };

	static SDL_Texture* Pencil;
	static SDL_Rect pencilTransform;

	static SDL_Rect eraserTransform;
	static void eraseArea();

	static void UpdateCursor();


};

	