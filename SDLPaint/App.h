#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
class App
{
public:
	//auto gameStatus - gameScreen
	App();
	~App();
	bool gameEnded;
	void GameScene();


private:

	//SDL_Texture* textTexture;
	//SDL_Texture* imageTexture;
	static int numberOfTrys;

};

