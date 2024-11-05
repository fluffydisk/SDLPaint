#include "App.h"
#include "Engine.h"
#include "DrawArea.h"
#include "MenuBar.h"
#include "Mouse.h"

App::App()
{
    gameEnded = false;
}

App::~App()
{
    //SDL_DestroyTexture(textTexture);
    //SDL_DestroyTexture(imageTexture);
}




void App::GameScene()
{
    DrawArea drawArea;
    MenuBar menuBar;
    while (!gameEnded)
    {
        DrawArea::createNewVector = false;
        
        Engine::UpdateFps();
        Engine::UpdateDeltaTime();
        while (SDL_PollEvent(&Engine::e) != 0) 
        {
            
            SDL_GetMouseState(&Engine::mouseX, &Engine::mouseY);
            if (Engine::mouseX < 0) Engine::mouseX = 0;
            if (Engine::mouseX > Engine::SCREEN_WIDTH) Engine::mouseX = Engine::SCREEN_WIDTH;
            if (Engine::mouseY < 0) Engine::mouseY = 0;
            if (Engine::mouseY > Engine::SCREEN_HEIGHT) Engine::mouseY = Engine::SCREEN_HEIGHT;

            if (Engine::e.type == SDL_QUIT) {

                gameEnded = true;
            }
            else if (Engine::e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (Engine::e.button.button == SDL_BUTTON_LEFT)
                {
                    if (Engine::leftMouse == false && Mouse::ableToDraw)
                    {
                        DrawArea::createNewVector = true;
                    }
                    Engine::leftMouse = true;
                }
                if (Engine::e.button.button == SDL_BUTTON_RIGHT)
                {
                    Engine::rigtMouse = true;
                }
            }
            else if (Engine::e.type == SDL_MOUSEBUTTONUP)
            {
                if (Engine::e.button.button == SDL_BUTTON_LEFT)
                {
                    Engine::leftMouse = false;
                }
                if (Engine::e.button.button == SDL_BUTTON_RIGHT)
                {
                    Engine::rigtMouse = false;
                }
            }
            else if (Engine::e.type == SDL_WINDOWEVENT) {
                if (Engine::e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    // Update screen width and height
                    SDL_GetWindowSize(Engine::window, &Engine::SCREEN_WIDTH, &Engine::SCREEN_HEIGHT);
                    std::cout << "Window resized to: " << Engine::SCREEN_WIDTH << "x" << Engine::SCREEN_HEIGHT << std::endl;
                }
            }   
        }

       

        //std::cout << drawArea.createNewVector << std::endl;
        //std::cout << Engine::FPS << std::endl;

        // Clear screen
        SDL_SetRenderDrawColor(Engine::renderer, 0xFF, 0xFF, 0xFF, 0xFF);//Background
        SDL_RenderClear(Engine::renderer);

        
        drawArea.Update();
        menuBar.Update();
        Mouse::Update();

        SDL_RenderPresent(Engine::renderer);
    }
}

