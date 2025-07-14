#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL3/SDL.h>

namespace RenderTools {
	class Graphics {
	public:
		Graphics() = delete;
		Graphics(int width, int height, char const* windowName);
		~Graphics();
		SDL_Renderer* getRenderer();
		SDL_Window* getWindow();
		void putPixel(int x, int y, Uint32 pixelValue);
		void clearPixelBuff(Uint32 const& clearColor); /*CALL BEFORE MODIFYING AND DRAWING SDL PIXEL TEXTURE*/
		void drawFromPixelBuff();
	private:
		int width;
		int height;
		Uint32* pixelBuffer; //Pixels used to be rendered on the screen
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* pixelTexture; //Actual texture for raw pixel buffer to be drawn to

	};


}




#endif