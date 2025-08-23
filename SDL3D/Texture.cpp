#include "Texture.hpp"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>

namespace Entity {
	Texture::Texture(const char* texturePath) : tex{ IMG_Load(texturePath) } {
		tex = SDL_ConvertSurface(tex, SDL_PIXELFORMAT_RGBA8888);
	}

	Uint32 Texture::getPixel(Sint16 x, Sint16 y) {
		if (x >= 0 && y >= 0 && x < this->tex->w && y < this->tex->h) {

			int bpp = SDL_BYTESPERPIXEL(this->tex->format);
			Uint8* pixel = (Uint8*)this->tex->pixels + y * this->tex->pitch + x * bpp;

			switch (bpp) {
			case 1:
				return *pixel;
			case 2:
				return *(Uint16*)pixel;
			case 3:
				#if SDL_BYTEORDER == SDL_BIG_ENDIAN
					return pixel[0] << 16 | pixel[1] << 8 | pixel[2];
				#else
					return pixel[0] | pixel[1] << 8 | pixel[2] << 16;
				#endif
			case 4:
				return *(Uint32*)pixel;
			}
		}
		return 0;
	}

	int Texture::getWidth() {
		return 600;
	}

	int Texture::getHeight() {
		return 600;
	}

	Texture::~Texture() {
		SDL_DestroySurface(tex);
	}
}
