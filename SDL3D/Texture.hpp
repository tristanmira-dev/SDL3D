#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>

namespace Entity {
	class Texture {
		public:
			Texture(const char* texturePath);
			~Texture();

			Uint32 getPixel(Sint16 x, Sint16 y);
			int getWidth();
			int getHeight();


		private:
			SDL_Surface* tex;
			int width;
			int height;

	};
}



#endif