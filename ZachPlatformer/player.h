#ifndef PLAYER_H_
#define PLAYER_H_

#include <map>

struct Sprite;
struct Graphics;

struct Player {
	Player(Graphics &graphics, int x, int y);

	void update(int elapesd_time_ms);
	void draw(Graphics &graphics);

	/* Movement */
	void startMovingLeft();
	void startMovingRight();
	void stopMovingVertically();
	void startMovingUp();
	void startMovingDown();
	void stopMovingHorizontally();
	void setRunning(bool isRunning);

	private:
		enum MotionType {
			STANDING,
			WALKING,
			RUNNING,
		};

		enum DirectionFacing {
			LEFT,
			RIGHT,
			UP,
			DOWN,
		};

		struct SpriteState {
			SpriteState(MotionType motion_type = STANDING, DirectionFacing direction_facing = LEFT) :
				motion_type(motion_type),
				direction_facing(direction_facing) {}
			MotionType motion_type;
			DirectionFacing direction_facing;
		};
		friend bool operator<(const SpriteState& a, const SpriteState& b);

		void initializeSprites(Graphics& graphics);
		SpriteState getSpriteState();

		int x_, y_;

		/* Movement */
		bool isRunning_;
		float velocity_x_;
		float acceleration_x_;
		float velocity_y_;
		float acceleration_y_;
		DirectionFacing direction_facing_;
		std::map<SpriteState, Sprite*> sprites_;
};

#endif // !PLAYER_H_