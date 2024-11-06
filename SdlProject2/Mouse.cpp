#include "Mouse.h"

SDL_Rect Mouse::eraserTransform;

SDL_Texture* Mouse::Pencil = nullptr;
SDL_Rect Mouse::pencilTransform;

bool Mouse::ableToDraw = false;
bool Mouse::erase = false;

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
	SDL_DestroyTexture(Pencil);
}

void Mouse::Update()
{
	UpdateCursor();
}

void Mouse::INIT()
{
	if (Pencil) {
		SDL_DestroyTexture(Pencil);		
	}

	Pencil = IMG_LoadTexture(Engine::renderer, "Dependencies/pencil.png");

	if (!Pencil)
	{
		SDL_Log("Failed to load pencil texture: %s", IMG_GetError());
	}
	eraserTransform = { 10, 10, 40, 40 };
	pencilTransform = { 10, 10, 20, 20 }; // Initial position
}

void Mouse::eraseArea()
{
	
	for (auto& everyDraw : DrawArea::allMouseDraws)
	{
		for (auto it = everyDraw->MouseDraws.begin(); it != everyDraw->MouseDraws.end(); ++it)
		{
			// Check if the current point is within the eraser area
			if ((it->x > eraserTransform.x && it->x < eraserTransform.x + eraserTransform.w) &&
				(it->y > eraserTransform.y && it->y < eraserTransform.y + eraserTransform.h))
			{
				// Replace point with break indicator instead of erasing
				*it = SDL_Point{ -1, -1 };
			}
		}
	}
}


void Mouse::UpdateCursor()
{
	bool cursorChanged = false; // Flag to track if the cursor has been updated

	if (Engine::mouseY < MenuBar::Background.y + MenuBar::Background.h && Engine::mouseY > MenuBar::Background.y)
	{

		ableToDraw = false;
		SDL_ShowCursor(SDL_ENABLE);

		for (std::map<int*, SDL_Rect> it : MenuBar::coloursList)
		{
			for (const auto& pB : it)
			{
				SDL_Rect colourRect = pB.second;

				if ((Engine::mouseY < colourRect.y + colourRect.h && Engine::mouseY > colourRect.y) &&
					Engine::mouseX < colourRect.x + colourRect.w && Engine::mouseX > colourRect.x)
				{

					if (!cursorChanged) {

						SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
						cursorChanged = true;
						if (Engine::leftMouse)
						{
							MenuBar::selectedColorTransform = { pB.second.x,pB.second.y + pB.second.h + 5, pB.second.w, 5 };
							DrawArea::pSelectedColor = pB.first;
						}
					}
					break;
				}
			}
		}
		if (!cursorChanged) {

			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));

		}
	}
	else
	{
		if (Engine::largerKeyboard)
		{
			DrawArea::brushSize++;
		}
		else if (Engine::smallerKeyboard)
		{
			DrawArea::brushSize--;
		}
		else if (Engine::rigtMouse)
		{
			SDL_SetRenderDrawColor(Engine::renderer, 0, 0, 0, 255);
			ableToDraw = false;
			SDL_ShowCursor(SDL_DISABLE);
			eraserTransform = { Engine::mouseX-10, Engine::mouseY-10, 40, 40 };
			SDL_SetRenderTarget(Engine::renderer, nullptr);

			SDL_RenderDrawRect(Engine::renderer, &eraserTransform);

			eraseArea();
			//SDL_SetRenderTarget(Engine::renderer, nullptr);
		}
		else
		{
			ableToDraw = true;
			SDL_ShowCursor(SDL_DISABLE);
			pencilTransform = { Engine::mouseX, Engine::mouseY - 17, 20, 20 };

			SDL_SetRenderTarget(Engine::renderer, nullptr);

			SDL_RenderCopy(Engine::renderer, Mouse::Pencil, nullptr, &pencilTransform);
		}
	}
}