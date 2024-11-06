#include "Engine.h"

int main(int argc, char* argv[]) 
{
    Engine engine;

    engine.Start();
    engine.~Engine();

    return 0;
}
