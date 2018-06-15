#include <SDL2/SDL.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "globals.hpp"
#include "Utils.hpp"
#include "SDL2_framework/Game.h"
// #include "State/Play.hpp"
#include "ResourceManager.hpp"
#include <libgen.h>

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

void _prepareTilesets(std::string binaryPath, Game *g);

int main(int argc, char* args[]) {
	time_t t;
	srand((unsigned int) time(&t));
	Game* g;
	char buffer[PATH_MAX];
	std::string binaryPath;
	Uint32 frameStart, frameTime;

	Utils::createFolder(Utils::getDataPath().c_str());

	char *res = realpath(dirname(args[argc - argc]), buffer);
	if (!res) {
		return 1;
	}

	binaryPath = buffer;
	g = Game::Instance();
	g->setBinaryPath(binaryPath);
	if (!g->init("Morph", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, FULL_SCREEN)) {
		Game::freeGame();
		return 1;
	}

	// g->getStateMachine()->changeState(new PlayState());
	while (g->isRunning()) {
		frameStart = SDL_GetTicks();
		InputUpdateResult result = g->handleEvents();
		if (result == HAS_EVENT) {
			g->update();
		}
		g->render();

		// use a delay to cap the fps
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - frameTime);
		}
	}

	Game::freeGame();

	return 0;
}
