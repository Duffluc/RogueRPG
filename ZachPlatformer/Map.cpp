#include "game.h"
#include "map.h"
#include "Sprite.h"
#include "graphics.h"

using std::vector;

Map* Map::createMap(Graphics &graphics) {
	Map* map = new Map();

	const int num_rows = 19;
	const int num_cols = 25;


	map->foreground_sprites_ = vector<vector <Sprite*>> (num_rows, vector<Sprite*> (num_cols));
	const int row = 11;
	Sprite* sprite = new Sprite("resources/PrtCave.bmp", graphics, Game::tileSize, 0, Game::tileSize, Game::tileSize);
	for (int col = 0; col < num_cols; col++) {
		map->foreground_sprites_[row][col] = sprite;
	}

	return map;
}

void Map::update(int elapsed_time_ms) {
	for (size_t row = 0; row < foreground_sprites_.size(); row++) {
		for (size_t col = 0; col < foreground_sprites_[row].size(); col++) {
			if (foreground_sprites_[row][col]) {
				foreground_sprites_[row][col]->update(elapsed_time_ms);
			}
		}
	}
}

void Map::draw(Graphics &graphics) const {
	for (size_t row = 0; row < foreground_sprites_.size(); row++) {
		for (size_t col = 0; col < foreground_sprites_[row].size(); col++) {
			if (foreground_sprites_[row][col]) {
				foreground_sprites_[row][col]->draw(graphics, col * Game::tileSize, row*Game::tileSize);
			}
		}
	}
}