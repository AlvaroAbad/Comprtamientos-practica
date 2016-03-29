#include "..\include\appstategame.h"
#include "../include/game.h"

extern Game *game;

void AppStateGame::run()
{
	game->run();
}

void AppStateGame::draw() const
{
	game->draw();
}

void AppStateGame::getInputs()
{
	game->getInput();
}

void AppStateGame::activate()
{
	if (!game) {
		game = new Game();
		game->initialize();
	}
}

void AppStateGame::deactivate()
{
}
