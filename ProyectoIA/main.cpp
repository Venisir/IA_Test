#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    Game* game = Game::Instance();
    game->Run();
    
    return 0;
}