#include "graphics.h"
#include "SDL.h"

namespace {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int FPS = 60;
	const int BPS = 32;
}

/* Graphics Constructor */
Graphics::Graphics() {
	for (SpriteMap::iterator iter = sprite_sheets_.begin(); iter != sprite_sheets_.end(); iter++) {
		SDL_FreeSurface(iter->second);
	}
	screen_ = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BPS, 0);
	SDL_ShowCursor(SDL_DISABLE);
}

/* Graphics Destructor */
Graphics::~Graphics() {
	SDL_FreeSurface(screen_);
}

Graphics::SurfaceID Graphics::loadImage(const std::string& file_path) {
	/* If we havent loaded in the spritesheet, load it in now. */
	if (sprite_sheets_.count(file_path) == 0) {
		sprite_sheets_[file_path] = SDL_LoadBMP(file_path.c_str());
	}
	return sprite_sheets_[file_path];
}

void Graphics::BlitSurface(SDL_Surface* source, SDL_Rect* source_rect, SDL_Rect* dest_rect) {
	SDL_BlitSurface(source, source_rect, screen_, dest_rect);
}

void Graphics::clear() {
	SDL_FillRect(screen_, NULL, 0);
}

void Graphics::flip() {
	SDL_Flip(screen_);
}
