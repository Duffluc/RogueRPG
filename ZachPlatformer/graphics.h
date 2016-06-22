#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <map>
#include <string>

struct SDL_Surface;
struct SDL_Rect;

struct Graphics {
	typedef SDL_Surface* SurfaceID;

	Graphics();
	~Graphics();

	SurfaceID loadImage(const std::string& file_path);

	void BlitSurface(
		SurfaceID source,
		SDL_Rect* source_rect, 
		SDL_Rect* dest_rect);

	void clear();

	void flip();

	private:
		typedef std::map<std::string, SDL_Surface*> SpriteMap;
		SpriteMap sprite_sheets_;
		SDL_Surface* screen_;
};

#endif