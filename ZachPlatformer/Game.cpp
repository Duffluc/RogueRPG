#include "game.h"

#include "SDL.h"

#include "player.h"
#include "input.h"
#include "graphics.h"
#include "map.h"
#include "AnimatedSprite.h"

namespace {
	const int FPS = 60;
}

// Static
int Game::tileSize = 32;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	eventLoop();
}

Game::~Game() {
	SDL_Quit();
}

/* Main game event loop. 
 *	Runs at 60 Hz.
 *	Handles inputs 
 *  Update sprites
 *  Check collisions 
 *  Draw Screen */
void Game::eventLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;
	player_ = new Player(graphics, 400, 300);
	map_ = Map::createMap(graphics);

	bool running = true;
	while (running) {
		const int start_time_ms = SDL_GetTicks();
		input.beginNewFrame();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				input.keyDownEvent(event);
				break;
			case SDL_KEYUP:
				input.keyUpEvent(event);
				break;
			default:
				break;
			}
		}

		/* Exit the game */
		if (input.wasKeyPressed(SDLK_ESCAPE)) {
			running = false;
		}

		/* Player Movement */
		if (input.isKeyHeld(SDLK_UP) && input.isKeyHeld(SDLK_DOWN)) {
			player_->stopMovingVertically();
		}
		else if (input.isKeyHeld(SDLK_UP)) {
			player_->startMovingUp();
		}
		else if (input.isKeyHeld(SDLK_DOWN)) {
			player_->startMovingDown();
		}
		else {
			player_->stopMovingVertically();
		}
		
		if (input.isKeyHeld(SDLK_LEFT) && input.isKeyHeld(SDLK_RIGHT)) {
			player_->stopMovingHorizontally();
		} else if (input.isKeyHeld(SDLK_LEFT)) {
			player_->startMovingLeft();
		} else if (input.isKeyHeld(SDLK_RIGHT)) {
			player_->startMovingRight();
		} else {
			player_->stopMovingHorizontally();
		}

		if (input.isKeyHeld(SDLK_RSHIFT)) {
			player_->setRunning(true);
		}
		else {
			player_->setRunning(false);
		}
		
		/* Update locations */
		update(20);

		/* Draw to the screen */
		draw(graphics);
		
		/* Keep the game running at max 60 fps */
		const int delay = 1000 / FPS - (SDL_GetTicks() - start_time_ms);
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}
}

void Game::update(int elapsed_time_ms) {
	player_->update(elapsed_time_ms);
	map_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
	graphics.clear();
	player_->draw(graphics);
	map_->draw(graphics);
	graphics.flip();
}