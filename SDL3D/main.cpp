#define _CRTDBG_MAP_ALLOC

#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "Graphics.hpp"
#include "Color.hpp"
#include "Shapes.hpp"
#include "Model.hpp"
#include "Vertex.hpp"
#include "GameObject.hpp"
#include "RenderEntity.hpp"
#include "Math.hpp"
#include <crtdbg.h>
#include <vector>
#include <initializer_list>



int main(int argc, char **argv) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	RenderTools::Graphics graphics(1000, 900, "WINDOW");
	SDL_Event event{};
	
	Entity::Model model{
		Geometry::VertexData{
			Linear::Vector3D{0.5f, 0.5f, 1.f},
			1.f,
			Utils::Color{0xFF0000FF}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, 0.5f, 1.f},
			1.f,
			Utils::Color{0xFF0000FF}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, -0.5f, 1.f},
			1.f,
			Utils::Color{0x0000FFFF}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, -0.5f, 1.f},
			1.f,
			Utils::Color{0xFF0000FF}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, 0.5f, -1.f},
			1.f,
			Utils::Color{0x00FF00FF}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, 0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFF0000FF}
		}
	};

	Entity::Camera camera{ Linear::Vector3D{0.f, 0.f, 0.f}, Entity::Rotation{0.f, 0.f, 0.f} };

	model.insertTriangle(0, 1, 2);
	model.insertTriangle(0, 2, 3);
	model.insertTriangle(4, 0, 3);
	model.insertTriangle(4, 3, 7);
	model.insertTriangle(5, 4, 7);
	model.insertTriangle(5, 7, 6);
	model.insertTriangle(1, 5, 6);
	model.insertTriangle(1, 6, 2);
	model.insertTriangle(4, 5, 1);
	model.insertTriangle(4, 1, 0);
	model.insertTriangle(2, 6, 7);
	model.insertTriangle(2, 7, 3);

	/*GAME LOOP*/
	while (true) {

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:

				return 0;
			}
		}
		graphics.clearPixelBuff(0x0);
		graphics.resetZBuffer();

		//model.renderGameObj(graphics);
		Entity::GameObject a{ Linear::Vector3D{-3.f, 0.f, 7.5f}, Linear::Vector3D{1.f, 1.f, 1.f}, Entity::Rotation{0.f, 0.f, 0.f } };
		Entity::GameObject b{ Linear::Vector3D{1.f, 0.f, 4.f}, Linear::Vector3D{1.f, 1.f, 1.f}, Entity::Rotation{0.f, 0.f, 0.f } };
		Entity::GameObject c{ Linear::Vector3D{0.5f, 0.f, 6.f}, Linear::Vector3D{1.f, 1.f, 1.f}, Entity::Rotation{100.f, 80.f, 0.f } };

		/*RenderTools::drawInterpolatedTri(graphics, Geometry::Triangle{
			Geometry::VertexData{
				Linear::Vector3D{200.f, 0.f, 0.f},
				1.f,
				Utils::Color{0xFF0000FF}
			},
			Geometry::VertexData{
				Linear::Vector3D{700.f, 0.f, 0.f},
				1.f,
				Utils::Color{0x00FF00FF}
			},
			Geometry::VertexData{
				Linear::Vector3D{200.f, 500.f, 0.f},
				1.f,
				Utils::Color{0x0000FFFF}
			}
		});*/

		Entity::renderEntity(camera, model, a, graphics);
		Entity::renderEntity(camera, model, b, graphics);

		graphics.drawFromPixelBuff();

	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}