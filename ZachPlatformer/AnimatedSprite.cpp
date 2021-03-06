#include "AnimatedSprite.h"
#include "game.h"

AnimatedSprite::AnimatedSprite(const std::string& file_path,
	Graphics& graphics,
	int source_x, int source_y,
	int width, int height,
	int fps, int num_frames) :
	Sprite(file_path, graphics, source_x, source_y, width, height),
	frame_time_(1000 / fps),
	num_frames_(num_frames),
	current_frame_(0),
	elapsed_time_(0) {

}

void AnimatedSprite::update(int elapsed_time_ms) {
	elapsed_time_ = elapsed_time_ + elapsed_time_ms;
	if (elapsed_time_ >= frame_time_) {
		current_frame_++;
		elapsed_time_ = 0;
		if (current_frame_ < num_frames_) {
			source_rect_.x = source_rect_.x + Game::tileSize;
		} else {
			source_rect_.x = source_rect_.x - Game::tileSize * (num_frames_ - 1);
			current_frame_ = 0;
		}
	}
}