#include "DrawArea.h"

bool DrawArea::createNewVector = false;
std::vector<std::vector<SDL_Point>*> DrawArea::allMouseDraws;

DrawArea::DrawArea() : singleMouseDraw(nullptr), drawTexture(nullptr)
{

}

DrawArea::~DrawArea()
{
    drawTexture = nullptr;
    for (std::vector<SDL_Point>* pointers : allMouseDraws)
    {
        delete pointers;
    }
    allMouseDraws.clear();
}

void DrawArea::Update()
{
    handleInput();
    DrawToScreen();
}

void DrawArea::clearScreen()
{
    for (std::vector<SDL_Point>* pointers : allMouseDraws)
    {
        delete pointers;
    }
    allMouseDraws.clear();
    allMouseDraws.shrink_to_fit();
    singleMouseDraw = nullptr;
}

void DrawArea::handleInput()
{
    if (createNewVector)
    {
        singleMouseDraw = new std::vector<SDL_Point>();
        allMouseDraws.push_back(singleMouseDraw);
        createNewVector = false;
    }

    if (Engine::leftMouse && singleMouseDraw && Mouse::ableToDraw)
    {
        singleMouseDraw->push_back(SDL_Point{ Engine::mouseX, Engine::mouseY });
    }

    if (Engine::rigtMouse)
    {
        //clearScreen();
    }
}


void DrawArea::DrawToScreen()
{
    int brushSize =3; //add feature for editing brush size, you can do it by in allMouseDraws vector you can map the drawing points with brush size
    SDL_SetRenderDrawColor(Engine::renderer, 0, 0, 0, 255);

    for (std::vector<SDL_Point>* points : allMouseDraws)
    {
        if (!points->empty())
        {
            for (size_t i = 0; i < points->size() - 1; ++i) 
            {
                // Check if the current point or the next point is a "break"
                if (points->at(i).x == -1 && points->at(i).y == -1) continue;
                if (points->at(i + 1).x == -1 && points->at(i + 1).y == -1) continue;

                // Draw line with thicker brush
                SDL_Point p1 = points->at(i);
                SDL_Point p2 = points->at(i + 1);

                if (brushSize > 1) 
                {
                    // Draw multiple rectangles along the line to simulate thickness
                    for (int dx = -brushSize / 2; dx <= brushSize / 2; ++dx)
                    {
                        for (int dy = -brushSize / 2; dy <= brushSize / 2; ++dy)
                        {
                            SDL_RenderDrawLine(Engine::renderer,
                                p1.x + dx, p1.y + dy,
                                p2.x + dx, p2.y + dy);
                        }
                    }
                }
                else
                {
                    // Regular line drawing for small brush sizes
                    SDL_RenderDrawLine(Engine::renderer, p1.x, p1.y, p2.x, p2.y);
                }
            }
        }
    }
}

