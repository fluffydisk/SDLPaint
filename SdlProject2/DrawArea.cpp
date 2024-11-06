#include "DrawArea.h"

bool DrawArea::createNewVector = false;
std::vector<DrawArea::singleDraw*> DrawArea::allMouseDraws;
int* DrawArea::pSelectedColor = Engine::COLORS::BLACK;
int DrawArea::brushSize = 1;


DrawArea::DrawArea() : currentDraw(nullptr), drawTexture(nullptr)
{

}

DrawArea::~DrawArea()
{
    drawTexture = nullptr;
    for (auto& it : allMouseDraws)
    {
        delete it;
    }
    allMouseDraws.clear();
}

void DrawArea::Update()
{

    //std::cout << createNewVector << std::endl;
    handleInput();
    DrawToScreen();
}

void DrawArea::clearScreen()
{
    for (auto* it : allMouseDraws)
    {
        delete it; 
    }
    allMouseDraws.clear();
    allMouseDraws.shrink_to_fit();
    currentDraw = nullptr;
}

void DrawArea::handleInput()
{
    if (createNewVector)
    {
        currentDraw = new singleDraw();
        allMouseDraws.push_back(currentDraw);
        createNewVector = false;
    }

    if (Engine::leftMouse && currentDraw && Mouse::ableToDraw)
    {
        currentDraw->MouseDraws.push_back(SDL_Point{ Engine::mouseX, Engine::mouseY });
        currentDraw->SelectedColor = pSelectedColor;
        currentDraw->BrushSize = brushSize;
    }
}


void DrawArea::DrawToScreen()
{

    for (auto&points : allMouseDraws)
    {
        int _burshSize = points->BrushSize;
        SDL_SetRenderDrawColor(Engine::renderer, points->SelectedColor[0], points->SelectedColor[1], points->SelectedColor[2], points->SelectedColor[3]);
        if (!points->MouseDraws.empty())
        {
            for (size_t i = 0; i < points->MouseDraws.size() - 1; ++i)
            {
                // Check if the current point or the next point is a "break"
                if (points->MouseDraws.at(i).x == -1 && points->MouseDraws.at(i).y == -1) continue;
                if (points->MouseDraws.at(i + 1).x == -1 && points->MouseDraws.at(i + 1).y == -1) continue;

                // Draw line with thicker brush
                SDL_Point p1 = points->MouseDraws.at(i);
                SDL_Point p2 = points->MouseDraws.at(i + 1);

                if (_burshSize > 1)
                {
                   
                    for (int dx = -_burshSize / 2; dx <= _burshSize / 2; ++dx)
                    {
                        for (int dy = -_burshSize / 2; dy <= _burshSize / 2; ++dy)
                        {
                            SDL_RenderDrawLine(Engine::renderer,
                                p1.x + dx, p1.y + dy,
                                p2.x + dx, p2.y + dy);
                        }
                    }
                }
                else
                {
                   
                    SDL_RenderDrawLine(Engine::renderer, p1.x, p1.y, p2.x, p2.y);
                }
            }
        }
    }
}

