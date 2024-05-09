#include "Game.hpp"

int main()
{
    srand(time(0));

    CLISNAKE::Game game(40, 20);
    game.run();

    return 0;
};