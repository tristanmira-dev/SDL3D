#include "Shapes.hpp"
#include "Graphics.hpp"
#include "Vector2D.hpp"
#include "Math.hpp"
#include "Color.hpp"

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>

namespace {
	Geometry::VertexData const *& min(Geometry::VertexData const *& p0, Geometry::VertexData const *& p1) {
		return p0->coord.y < p1->coord.y ? p0 : p1;
	}

	/*TODO CHANGE TO NOT MUTATE VEC1*/
	template<typename T>
	void concat(T& vec1, T const& src) {
		typename T::const_iterator start{ src.begin() };
		typename T::const_iterator end{ src.end() };
		start++;

		for (typename T::const_iterator x{ start }; x < end; ++x) {
			vec1.emplace_back(*x);
		}

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
				
			std::vector<int> values{ Math::interpolateInt(static_cast<int>(newP0->x), newP0->y, static_cast<int>(newP1->x), newP1->y) };

			for (int x{ static_cast<int>(newP0->x) }; x <= newP1->x; ++x) {
				renderer.putPixel(x, values[static_cast<int>(x - newP0->x)], color);
			}
		}
		else {

			if (newP0->y > newP1->y) std::swap(newP0, newP1);

			std::vector<int> values{ Math::interpolateInt(static_cast<int>(newP0->y), newP0->x, static_cast<int>(newP1->y), newP1->x) };

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

	void drawTriangle(RenderTools::Graphics& renderer, Geometry::Triangle const& tri, Utils::Color const &color) {

		int maxWidth{ renderer.getWidth() };
		int maxHeight{ renderer.getHeight() };

		Geometry::VertexData const* p0{ &(tri.vertices[0]) };
		Geometry::VertexData const* p1{ &(tri.vertices[1]) };
		Geometry::VertexData const* p2{ &(tri.vertices[2]) };

		/*SWAP coord such that y goes up to ascending order*/
		std::swap(p0, min(min(p0, p1), p2)); std::swap(p1, min(p1, p2));

		//in a flat bottom/flat top triangle, x12/x01 respectively will only have 1 element (Since the independant variables (y) are the same for 2 points)
		std::vector<int> x01{ Math::interpolateInt(static_cast<int>(p0->coord.y), p0->coord.x, static_cast<int>(p1->coord.y), p1->coord.x) };
		std::vector<int> x12{ Math::interpolateInt(static_cast<int>(p1->coord.y), p1->coord.x, static_cast<int>(p2->coord.y), p2->coord.x) };
		std::vector<int> x02{ Math::interpolateInt(static_cast<int>(p0->coord.y), p0->coord.x, static_cast<int>(p2->coord.y), p2->coord.x) };

		/*x01 will contain the full set of x values of two sides, x01 and x12 for now*/
		concat(x01, x12);

		int m{ static_cast<int>(std::floor(x02.size() / 2)) };
		
		std::vector<int> left_x;
		std::vector<int> right_x;
		
		/*CHECK WHICH SIDE OF X VALUES ARE LEFT OR RIGHT*/
		if (x01[m] < x02[m]) {
			left_x = x01;
			right_x = x02;
		} else {
			right_x = x01;
			left_x = x02;
		}

		for (int y{ static_cast<int>(p0->coord.y) }; y <= static_cast<int>(p2->coord.y); ++y) {
			int currentY{ y - static_cast<int>(p0->coord.y) };

			for (int x{ left_x[currentY] }; x <= right_x[currentY]; ++x) {
				renderer.putPixel(x,  y, color.colorVal);
			}
		}

	}

	void drawShadedTriangle(RenderTools::Graphics& renderer, Geometry::Triangle const& tri, Utils::Color const &color) {

		Geometry::VertexData const* p0{ &(tri.vertices[0]) };
		Geometry::VertexData const* p1{ &(tri.vertices[1]) };
		Geometry::VertexData const* p2{ &(tri.vertices[2]) };

		/*SWAP coord such that y goes up to ascending order*/
		std::swap(p0, min(min(p0, p1), p2)); std::swap(p1, min(p1, p2));

		std::vector<int> x01{ Math::interpolateInt(static_cast<int>(p0->coord.y), p0->coord.x, static_cast<int>(p1->coord.y), p1->coord.x) };
		std::vector<float> h01{ Math::interpolateFloat(p0->coord.y, p0->h, p1->coord.y, p1->h) };


		std::vector<int> x12{ Math::interpolateInt(static_cast<int>(p1->coord.y), p1->coord.x, static_cast<int>(p2->coord.y), p2->coord.x) };
		std::vector<float> h12{ Math::interpolateFloat(p1->coord.y, p1->h, p2->coord.y, p2->h) };

		std::vector<int> x02{ Math::interpolateInt(static_cast<int>(p0->coord.y), p0->coord.x, static_cast<int>(p2->coord.y), p2->coord.x) };
		std::vector<float> h02{ Math::interpolateFloat(p0->coord.y, p0->h, p2->coord.y, p2->h) };


		concat(x01, x12);
		concat(h01, h12);

		int midpoint{ static_cast<int>(std::floor(x01.size() / 2.f)) };

		std::vector<int> x_left;
		std::vector<int> x_right;

		std::vector<float> h_left;
		std::vector<float> h_right;


		if (x01[midpoint] < x02[midpoint]) {

			x_left = x01;
			x_right = x02;

			h_left = h01;
			h_right = h02;

		} else {

			x_right = x01;
			x_left = x02;

			h_right = h01;
			h_left = h02;
		
		}

		int yEnd{ static_cast<int>(p2->coord.y) };
		int yStart{ static_cast<int>(p0->coord.y) };

		for (int y{ static_cast<int>(p0->coord.y) }; y < yEnd; ++y) {

			int xStart{ x_left[y - yStart] };
			int xEnd{ x_right[y - yStart] };


			
			std::vector<float> hInterpolated { 
				Math::interpolateFloat(static_cast<float>(xStart), h_left[y-yStart], static_cast<float>(xEnd), h_right[y-yStart]) 
			};

			for (int x{ xStart }; x < xEnd; ++x) {
				renderer.putPixel(x, y, color * hInterpolated[x - xStart]);
			}
		}

	}


}
