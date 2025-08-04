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

	RenderTools::Graphics graphics(1000, 800, "WINDOW");
	SDL_Event event{};

	std::vector<int> test{ Math::interpolateInt(1, 2, 10, 5) };
	
	Entity::Model model{
		Geometry::VertexData{
			Linear::Vector3D{0.5f, 0.5f, 1.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, 0.5f, 1.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, -0.5f, 1.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, -0.5f, 1.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, 0.5f, -1.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, 0.5f, -1.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, -0.5f, -1.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, -0.5f, -1.f}
		}
	};

	Entity::Camera camera{ Linear::Vector3D{0.f, 0.f, 0.f}, Entity::Rotation{25.f, 0.f, 0.f} };

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
		graphics.clearPixelBuff(0);

		//model.renderGameObj(graphics);
		Entity::GameObject a{ Linear::Vector3D{-1.f, -1.5f, 5.f}, Linear::Vector3D{0.5f, 0.5f, 1.f}, Entity::Rotation{0.f, 100.f, 0.f } };
		Entity::GameObject b{ Linear::Vector3D{0.f, 0.f, 5.f}, Linear::Vector3D{0.5f, 0.5f, 1.f}, Entity::Rotation{0.f, 0.f, 0.f } };

		/*Entity::renderEntity(camera, model, gameObj, graphics);
		Entity::renderEntity(camera, model, gameObj2, graphics);*/
		Entity::renderEntity(camera, model, a, graphics);
		Entity::renderEntity(camera, model, b, graphics);
	
		graphics.drawFromPixelBuff();

	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}