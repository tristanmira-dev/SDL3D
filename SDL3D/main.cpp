#define _CRTDBG_MAP_ALLOC

#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "Graphics.hpp"
#include "Color.hpp"
#include "Shapes.hpp"
#include "Vertex.hpp"
#include <crtdbg.h>



int main(int argc, char **argv) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

		Geometry::Triangle triangle(Geometry::VertexData{ Linear::Vector3D {0.f, 0.f}, 0.3f },
			Geometry::VertexData{ Linear::Vector3D {200.f, 599.f}, 0.8f },
			Geometry::VertexData{ Linear::Vector3D {400.f, 599.f}, 1.f },
			Linear::Vector3D{}
		);

		RenderTools::drawLine(graphics, Linear::Vector2D{ 400.f, -250.f }, Linear::Vector2D{ 400.f, 250.f }, 0x00FF00FF);
		//RenderTools::drawWireFrameTriangle(graphics, triangle, 0xFFFFFFFF);
		//RenderTools::drawShadedTriangle(graphics, triangle, Utils::Color{0xFF0000FF});

		// The four "front" vertices
		Linear::Vector3D vAf{ -2, -2.f, 3 };
		Linear::Vector3D vBf{ -2, 2.f, 3 };
		Linear::Vector3D vCf{ 1, 2.f, 3 };
		Linear::Vector3D vDf{ 1, -2.f, 3 };

		Linear::Vector3D vAb{ -2, -2.f, 4 };
		Linear::Vector3D vBb{ -2, 2.f, 4 };
		Linear::Vector3D vCb{ 1, 2.f, 4 };
		Linear::Vector3D vDb{ 1, -2.f, 4 };



		RenderTools::drawLine(graphics, vAf.project(graphics), vBf.project(graphics), 0x00FF00FF);
		RenderTools::drawLine(graphics, vBf.project(graphics), vCf.project(graphics), 0x00FF00FF);
		RenderTools::drawLine(graphics, vCf.project(graphics), vDf.project(graphics), 0x00FF00FF);
		RenderTools::drawLine(graphics, vDf.project(graphics), vAf.project(graphics), 0x00FF00FF);

		RenderTools::drawLine(graphics, vAb.project(graphics), vBb.project(graphics), 0x00FF00FF);
		RenderTools::drawLine(graphics, vBb.project(graphics), vCb.project(graphics), 0x00FF00FF);
		RenderTools::drawLine(graphics, vCb.project(graphics), vDb.project(graphics), 0x00FF00FF);
		RenderTools::drawLine(graphics, vDb.project(graphics), vAb.project(graphics), 0x00FF00FF);

		graphics.drawFromPixelBuff();

	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}