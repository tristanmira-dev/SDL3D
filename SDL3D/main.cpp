#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "Graphics.hpp"

int main(int argc, char **argv) {

	RenderTools::Graphics graphics(800, 600, "WINDOW");
	SDL_Event event{};

	/*GAME LOOP*/
	while (true) {

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_WINDOW_CLOSE_REQUESTED:

					return 0;
			}
		}
		graphics.clearPixelBuff(0);
		for (int i = 0; i < 800; ++i) {
			graphics.putPixel(i, 300, 0xFF0000FF);
		}
		
		graphics.drawFromPixelBuff();

		SDL_RenderPresent(graphics.getRenderer());
	}
	

	return 0;
}