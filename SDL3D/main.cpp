#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "Graphics.hpp"
#include "Shapes.hpp"
#include "Vertex.hpp"


int main(int argc, char **argv) {

	RenderTools::Graphics graphics(1000, 600, "WINDOW");
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

		Geometry::Triangle triangle(Geometry::VertexData{ Linear::Vector3D {0.f, 0.f} },
			Geometry::VertexData{ Linear::Vector3D {400.f, 0.f} },
			Geometry::VertexData{ Linear::Vector3D {0.f, 599.f} },
			Linear::Vector3D{});

		RenderTools::drawLine(graphics, Linear::Vector2D{400.f, 350.f}, Linear::Vector2D{ 400.f, 300.f }, 0x00FF00FF);
		RenderTools::drawWireFrameTriangle(graphics, triangle, 0x0000FFFF);
		
		graphics.drawFromPixelBuff();

	}
	

	return 0;
}