#include "player.h"
#include "game.h"
#include "AnimatedSprite.h"

#include <cmath>
#include <algorithm>

namespace {
	const float kSlowDown = 0.8f;
	const float kAcceleration = 0.0012f;	// (pixels /ms) / ms
	const float kMaxSpeed = 0.325f;			// pixels / ms
	const float kMaxSpeedRunning = 0.7f;
}

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b) {
	if (a.motion_type != b.motion_type) {
		return a.motion_type < b.motion_type;
	}

	if (a.direction_facing != b.direction_facing) {
		return a.direction_facing < b.direction_facing;
	}
	return false;
}

void Player::initializeSprites(Graphics& graphics) {
	sprites_[SpriteState(STANDING, LEFT)] = new Sprite("resources/MyChar.bmp", graphics, 0, 0, Game::tileSize, Game::tileSize);
	sprites_[SpriteState(WALKING, LEFT)] = new AnimatedSprite("resources/MyChar.bmp", graphics, 0, 0, Game::tileSize, Game::tileSize, 15, 3);
	sprites_[SpriteState(STANDING, RIGHT)] = new Sprite("resources/MyChar.bmp", graphics, 0, Game::tileSize, Game::tileSize, Game::tileSize);
	sprites_[SpriteState(WALKING, RIGHT)] = new AnimatedSprite("resources/MyChar.bmp", graphics, 0, Game::tileSize, Game::tileSize, Game::tileSize, 15, 3);
}


Player::SpriteState Player::getSpriteState() {
	return SpriteState(acceleration_x_ == 0.0f? STANDING : WALKING,
		direction_facing_);
}

Player::Player(Graphics& graphics, int x, int y) :
	x_(x),
	y_(y),
	isRunning_(false),
	velocity_x_(0.0f),
	acceleration_x_(0.0f),
	velocity_y_(0.0f),
	acceleration_y_(0.0f),
	direction_facing_(LEFT) {
	initializeSprites(graphics);
}

void Player::update(int elapesd_time_ms) {
	sprites_[getSpriteState()]->update(elapesd_time_ms);
	
	/* Movement */
	float maxSpeed;
	if (isRunning_) {
		maxSpeed = kMaxSpeedRunning;
	} else {
		maxSpeed = kMaxSpeed;
	}
	x_ += round(velocity_x_ * elapesd_time_ms);
	velocity_x_ += acceleration_x_ * elapesd_time_ms;
	y_ += round(velocity_y_ * elapesd_time_ms);
	velocity_y_ += acceleration_y_ * elapesd_time_ms;

	if (acceleration_x_ < 0.0f) {
		velocity_x_ = std::max(velocity_x_, -maxSpeed);
	}
	else if (acceleration_x_ > 0.0f) {
		velocity_x_ = std::min(velocity_x_, maxSpeed);
	}
	else {
		velocity_x_ *= kSlowDown;
	}

	if (acceleration_y_ < 0.0f) {
		velocity_y_ = std::max(velocity_y_, -maxSpeed);
	}
	else if (acceleration_y_ > 0.0f) {
		velocity_y_ = std::min(velocity_y_, maxSpeed);
	}
	else {
		velocity_y_ *= kSlowDown;
	}
}

void Player::draw(Graphics &graphics) {
	sprites_[getSpriteState()]->draw(graphics, x_, y_);
}

/* Movement functions */
void Player::startMovingLeft() {
	direction_facing_ = LEFT;
	acceleration_x_ = -kAcceleration;
}

void Player::startMovingRight() {
	direction_facing_ = RIGHT;
	acceleration_x_ = kAcceleration;
}

void Player::stopMovingHorizontally() {
	acceleration_x_ = 0.0f;
}

void Player::startMovingUp() {
	acceleration_y_ = -kAcceleration;
}

void Player::startMovingDown() {
	acceleration_y_ = kAcceleration;
}

void Player::stopMovingVertically() {
	acceleration_y_ = 0.0f;
}

void Player::setRunning(bool isRunning) {
	isRunning_ = isRunning;
}