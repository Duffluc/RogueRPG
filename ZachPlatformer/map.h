#ifndef MAP_H_
#define MAP_H_

#include <vector>

struct Sprite;
struct Graphics;

struct Map {
	static Map* createMap(Graphics &graphics);

	void update(int elapsed_time_ms);
	void draw(Graphics &graphjics) const;

	private:
		std::vector<std::vector<Sprite*>> foreground_sprites_;

};

#endif //MAP_H_