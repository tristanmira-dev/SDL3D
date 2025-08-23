#define _CRTDBG_MAP_ALLOC

#include "Graphics.hpp"
#include "Color.hpp"
#include "Shapes.hpp"
#include "Model.hpp"
#include "Vertex.hpp"
#include "GameObject.hpp"
#include "RenderEntity.hpp"
#include "Math.hpp"
#include "Texture.hpp"

#include <crtdbg.h>
#include <vector>
#include <initializer_list>
#include <chrono>
#include <iostream>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>



int main(int argc, char **argv) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	RenderTools::Graphics graphics(1000, 900, "WINDOW");
	SDL_Event event{};
	
	/*Entity::Model model{
		Geometry::VertexData{
			Linear::Vector3D{0.5f, 0.5f, 1.f},
			1.f,
			Utils::Color{0xFF0000FF},
			Linear::Vector3D{1.f, 0.f, 0.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, 0.5f, 1.f},
			1.f,
			Utils::Color{0xFF0000FF},
			Linear::Vector3D{0.f, 0.f, 0.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, -0.5f, 1.f},
			1.f,
			Utils::Color{0x0000FFFF},
			Linear::Vector3D{0.f, 1.f, 0.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, -0.5f, 1.f},
			1.f,
			Utils::Color{0xFF0000FF},
			Linear::Vector3D{1.f, 1.f, 0.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, 0.5f, -1.f},
			1.f,
			Utils::Color{0x00FF00FF},
			Linear::Vector3D{1.f, 0.f, 0.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, 0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF},
			Linear::Vector3D{0.f, 0.f, 0.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{-0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF},
			Linear::Vector3D{0.f, 1.f, 0.f}
		},
		Geometry::VertexData{
			Linear::Vector3D{0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFF0000FF},
			Linear::Vector3D{1.f, 1.f, 0.f}
		}
	};*/

	Entity::Model model{
		/*FRONT SQUARE FACE*/
		Geometry::VertexData{ //0
			Linear::Vector3D{-0.5f, 0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF},
			Linear::Vector3D{0.f, 0.f, 0.f}
		},
		Geometry::VertexData{ //1
			Linear::Vector3D{0.5f, 0.5f, -1.f},
			1.f,
			Utils::Color{0x00FF00FF},
			Linear::Vector3D{1.f, 0.f, 0.f}
		},
		Geometry::VertexData{ //2
			Linear::Vector3D{0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFF0000FF},
			Linear::Vector3D{1.f, 1.f, 0.f}
		},

		Geometry::VertexData{ //3
			Linear::Vector3D{-0.5f, 0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF},
			Linear::Vector3D{0.f, 0.f, 0.f}
		},
		Geometry::VertexData{ //4
			Linear::Vector3D{0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFF0000FF},
			Linear::Vector3D{1.f, 1.f, 0.f}
		},
		Geometry::VertexData{ //5
			Linear::Vector3D{-0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF},
			Linear::Vector3D{0.f, 1.f, 0.f}
		},


		/*LEFT SQUARE FACE*/
		Geometry::VertexData{ //6
			Linear::Vector3D{-0.5f, 0.5f, 1.f},
			1.f,
			Utils::Color{0xFF0000FF},
			Linear::Vector3D{0.f, 0.f, 0.f}
		},
		Geometry::VertexData{ //7
			Linear::Vector3D{-0.5f, 0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF},
			Linear::Vector3D{1.f, 0.f, 0.f}
		},
		Geometry::VertexData{ //8
			Linear::Vector3D{-0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF},
			Linear::Vector3D{0.f, 1.f, 0.f}
		},

		Geometry::VertexData{ //9
			Linear::Vector3D{-0.5f, 0.5f, 1.f},
			1.f,
			Utils::Color{0xFF0000FF},
			Linear::Vector3D{0.f, 0.f, 0.f}
		},
		Geometry::VertexData{ //10
			Linear::Vector3D{-0.5f, -0.5f, -1.f},
			1.f,
			Utils::Color{0xFFFFFFFF},
			Linear::Vector3D{1.f, 1.f, 0.f}
		},
		Geometry::VertexData{ //11
			Linear::Vector3D{-0.5f, -0.5f, 1.f},
			1.f,
			Utils::Color{0x0000FFFF},
			Linear::Vector3D{0.f, 1.f, 0.f}
		}



	};

	Entity::Texture tex{ "./Assets/crate-texture.jpg" };

	Entity::Camera camera{ Linear::Vector3D{0.f, 0.f, 0.f}, Entity::Rotation{0.f, 0.f, 0.f} };

	/*model.insertTriangle(0, 1, 2);
	model.insertTriangle(0, 2, 3);

	model.insertTriangle(4, 0, 3);
	model.insertTriangle(4, 3, 7);*/

	model.insertTriangle(0, 1, 2);
	model.insertTriangle(3, 4, 5);

	model.insertTriangle(6, 7, 8);
	model.insertTriangle(9, 10, 11);

	/*model.insertTriangle(1, 5, 6);
	model.insertTriangle(1, 6, 2);

	model.insertTriangle(4, 5, 1);
	model.insertTriangle(4, 1, 0);

	model.insertTriangle(2, 6, 7);
	model.insertTriangle(2, 7, 3);*/

	/*model.insertTriangle(5,4,7);
	model.insertTriangle(5, 7, 6);*/
	//model.insertTriangle();

	//model.insertTriangle(5, 7, 6);

	//model.renderGameObj(graphics);
	Entity::GameObject a{ Linear::Vector3D{2.f, 0.f, 9.5f}, Linear::Vector3D{1.f, 1.f, 1.f}, Entity::Rotation{0.f, 0.f, 0.f } };
	Entity::GameObject b{ Linear::Vector3D{1.f, 0.f, 6.f}, Linear::Vector3D{1.f, 1.f, 1.f}, Entity::Rotation{0.f, 0.f, 0.f } };
	Entity::GameObject c{ Linear::Vector3D{0.5f, 0.f, 6.f}, Linear::Vector3D{1.f, 1.f, 1.f}, Entity::Rotation{100.f, 80.f, 0.f } };

	/*DELTA CALCULATION*/
	std::chrono::system_clock::time_point currentTime{ std::chrono::system_clock::now() };
	std::chrono::duration<float> deltaTime{};



	/*GAME LOOP*/
	while (true) {

		std::cout << 1 / deltaTime.count() << " FRAMES" << '\n';


		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:

				return 0;
			}
		}

		//a.setX(a.getPosition().x - 0.02f);

		/*DELTA TIME*/
		std::chrono::time_point newTime{ std::chrono::system_clock::now() };
		deltaTime = newTime - currentTime;
		currentTime = newTime;

		graphics.clearPixelBuff(0x0);
		graphics.resetZBuffer();

		

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

		//a.setZ(a.getPosition().z + 0.01f);

		Entity::renderEntity(camera, model, a, graphics, tex);
		//Entity::renderEntity(camera, model, b, graphics);
		

		graphics.drawFromPixelBuff();

	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}