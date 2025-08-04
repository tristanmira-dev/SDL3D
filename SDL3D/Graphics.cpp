#include "Graphics.hpp"
#include <algorithm>
#include <cstring>

/*TODO LOOK INTO FIXING THE ENDIAN-NESS FOR COLOR*/

namespace RenderTools {

	/*INIT WINDOW, RENDERER, PIXEL BUFFER/TEXTURE*/
	Graphics::Graphics(int width, int height, char const* windowName) : width{ width }, height{ height }, pixelBuffer{ new Uint32[width * height] } {

		SDL_CreateWindowAndRenderer(windowName, width, height, SDL_WINDOW_OPENGL, &window, &renderer);

		pixelTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

		std::fill(pixelBuffer, pixelBuffer + width * height, 0);

	}

	Graphics::~Graphics() {
		delete[] pixelBuffer;
		SDL_DestroyTexture(pixelTexture);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}

	SDL_Renderer* Graphics::getRenderer() {
		return renderer;
	}

	SDL_Window* Graphics::getWindow() {
		return window;
	}

	int Graphics::getHeight() const {
		return height;
	}
	int Graphics::getWidth() const {
		return width;
	}

	void Graphics::putPixel(int x, int y, Uint32 pixelValue) {

		pixelBuffer[y * width + x] = pixelValue;

	}

	void Graphics::clearPixelBuff(Uint32 const& clearColor) {
		std::memset(pixelBuffer, clearColor, sizeof(*pixelBuffer) * width * height);
	}

	void Graphics::drawFromPixelBuff() {
		/*USE LOCK TEXTURE INSTEAD*/
		SDL_UpdateTexture(pixelTexture, nullptr, pixelBuffer, sizeof(*pixelBuffer) * width);
		SDL_RenderTexture(renderer, pixelTexture, nullptr, nullptr);

		SDL_RenderPresent(renderer);
	}

}