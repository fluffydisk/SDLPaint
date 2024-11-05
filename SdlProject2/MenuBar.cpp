#include "MenuBar.h"

SDL_Rect MenuBar::Background;
std::vector<std::map<int*, SDL_Rect>> MenuBar::coloursList;

MenuBar::MenuBar() 
{
	Background = { 0, -1, Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT / 6 };
}

MenuBar::~MenuBar()
{

}

void MenuBar::colourMenu()
{
    coloursList.clear();
    static SDL_Rect rect = { 20, 5, Background.w / 3, Background.h - 10 };

    SDL_SetRenderDrawColor(Engine::renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(Engine::renderer, &rect);

    int colorX = rect.w/10 + rect.x;



    for (int* color : Engine::COLORS::ALL_COLOURS)
    {
        SDL_Rect colorRect = { colorX, rect.h/3+rect.y, rect.w / 5, rect.h/3 };
        std::map<int*, SDL_Rect> pB;
        pB[color] = colorRect;
        coloursList.push_back(pB);


        SDL_SetRenderDrawColor(Engine::renderer, color[0], color[1], color[2], 255);
        SDL_RenderFillRect(Engine::renderer, &colorRect);

        colorX += colorRect.w; 
    }
}

void MenuBar::drawMenus()
{
	colourMenu();
}

void MenuBar::Update()
{
	
	drawBackground();
	drawMenus();
	
}

void MenuBar::drawBackground()
{
	SDL_SetRenderDrawColor(Engine::renderer, 0, 0, 0, 255);

	Background = { 0, -1, Engine::SCREEN_WIDTH, 50 };

	SDL_RenderFillRect(Engine::renderer, &Background);
}