#ifndef GAME_H_
#define GAME_H_

struct Map;
struct Player;
struct Graphics;

struct Game {
	Game();
	~Game();

	static int tileSize;

	private:
		void eventLoop();
		void update(int elapsed_time_ms);
		void draw(Graphics& graphics);

		Player* player_;
		Map* map_;
};

#endif
