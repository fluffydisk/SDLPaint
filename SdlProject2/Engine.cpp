#include "Engine.h"
#include "App.h"
#include "Mouse.h"

bool Engine::engineShouldEnd = false;

int Engine::SCREEN_WIDTH = 640; 
int Engine::SCREEN_HEIGHT = 480;

int Engine::mouseX = 0;
int Engine::mouseY = 0;
bool Engine::rigtMouse = false;
bool Engine::leftMouse = false;
bool Engine::largerKeyboard = false;
bool Engine::smallerKeyboard = false;

float Engine::deltaTime = 0.0f;
float Engine::FPS = 0.0f; // Initialize FPS to zero
int Engine::frameCount = 0;
Uint32 Engine::lastFPSUpdate = SDL_GetTicks();

SDL_Event Engine::e;
TTF_Font* Engine::font = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
SDL_Window* Engine::window = nullptr;

int Engine::COLORS::BLUE[4] = { 0, 0, 255, 255 };
int Engine::COLORS::RED[4] = { 255, 0, 0, 255 };
int Engine::COLORS::GREEN[4] = { 0, 255, 0, 255 };
int Engine::COLORS::BLACK[4] = { 0,0,0,255 };
int* Engine::COLORS::ALL_COLOURS[4] = { Engine::COLORS::RED, Engine::COLORS::GREEN, Engine::COLORS::BLUE, Engine::COLORS::BLACK };


bool Engine::init()
{
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_image for PNG support
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Initialize SDL_mixer for audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    // Initialize SDL_ttf for fonts
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    // Create a window
    window = SDL_CreateWindow("SDL Paint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    font = TTF_OpenFont("Dependencies/test.ttf", 28);  // Ensure this path is correct
    Mouse::INIT();

    return true;
}

void Engine::UpdateDeltaTime() {
    Engine::frameCount++;
    static Uint32 lastFrameTime = SDL_GetTicks(); 
    Uint32 currentFrameTime = SDL_GetTicks(); 
    Engine::deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentFrameTime; 
}

void Engine::UpdateFps() {
    // Check if one second has passed
    if (SDL_GetTicks() - lastFPSUpdate >= 1000) {
        Engine::FPS = frameCount; // Update FPS to the current frame count
        frameCount = 0;   // Reset frame count
        lastFPSUpdate = SDL_GetTicks(); // Reset the last update time
    }
    // If a second hasn't passed yet, do nothing (FPS will be updated in the next call)
}

Engine::Engine()
{
    init();
	engineShouldEnd = false;
}

Engine::~Engine()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Engine::Start()
{
    
    App app;
    app.GameScene();
}