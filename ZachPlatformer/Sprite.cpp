#include "Sprite.h"
#include "graphics.h"

Sprite::Sprite(const std::string& file_path,
		Graphics& graphics,
		int source_x, int source_y,
		int width, int height) {
	sprite_sheet_ = graphics.loadImage(file_path);
	source_rect_.x = source_x;
	source_rect_.y = source_y;
	source_rect_.w = width;
	source_rect_.h = height;
}

void Sprite::draw(Graphics& graphics, int x, int y) {
	SDL_Rect dest_rect;
	dest_rect.x = x;
	dest_rect.y = y;
	graphics.BlitSurface(sprite_sheet_, &source_rect_, &dest_rect);
}