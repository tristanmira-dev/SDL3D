#include "Shapes.hpp"
#include "Graphics.hpp"
#include "Vector2D.hpp"
#include "Math.hpp"

#include <vector>
#include <cstdlib>
#include <algorithm>

namespace {
	Geometry::VertexData const *& min(Geometry::VertexData const *& p0, Geometry::VertexData const *& p1) {
		return p0->coord.y < p1->coord.y ? p0 : p1;
	}
}

namespace RenderTools {
	void drawLine(RenderTools::Graphics& renderer, Linear::Vector2D const& p0, Linear::Vector2D const& p1, Uint32 const &color) {
		
		Linear::Vector2D const* newP0{ &p0 };
		Linear::Vector2D const* newP1{ &p1 };



		if (std::abs(p0.x - p1.x) >= std::abs(p0.y - p1.y)) {

			if (newP0->x > newP1->x) { 
				std::swap(newP0, newP1);
			};
				
			std::vector<int> values{ Math::interpolate(newP0->x, newP0->y, newP1->x, newP1->y) };

			for (int x{ static_cast<int>(newP0->x) }; x <= newP1->x; ++x) {
				renderer.putPixel(x, values[static_cast<int>(x - newP0->x)], color);
			}
		}
		else {

			if (newP0->y > newP1->y) std::swap(newP0, newP1);

			std::vector<int> values{ Math::interpolate(newP0->y, newP0->x, newP1->y, newP1->x) };

			for (int y{ static_cast<int>(newP0->y) }; y <= newP1->y; ++y) {
				renderer.putPixel(values[static_cast<int>(y - newP0->y)], y, color);
			}
		}
		
		


	}
	void drawWireFrameTriangle(RenderTools::Graphics& renderer, Geometry::Triangle const& triangle, Uint32 const &color) {
		drawLine(renderer, triangle.vertices[0].coord, triangle.vertices[1].coord, color);
		drawLine(renderer, triangle.vertices[1].coord, triangle.vertices[2].coord, color);
		drawLine(renderer, triangle.vertices[2].coord, triangle.vertices[0].coord, color);
	}

	void drawTriangle(RenderTools::Graphics& renderer, Geometry::Triangle const& tri) {

		Geometry::VertexData const* p0{ &(tri.vertices[0]) };
		Geometry::VertexData const* p1{ &(tri.vertices[1]) };
		Geometry::VertexData const* p2{ &(tri.vertices[2]) };

		/*SWAP coord such that y goes up to ascending order*/
		std::swap(p0, min(min(p0, p1), p2)); std::swap(p1, min(p1, p2));






	}


}
