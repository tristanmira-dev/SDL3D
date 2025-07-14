#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "Graphics.hpp"
#include "Shapes.hpp"

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
		
		RenderTools::drawLine(graphics, Linear::Vector2D{400.f, 350.f}, Linear::Vector2D{ 400.f, 300.f }, 0xFF0000FF);

		
		graphics.drawFromPixelBuff();

	}
	

	return 0;
}