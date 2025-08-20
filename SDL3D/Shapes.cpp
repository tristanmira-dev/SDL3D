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

	void drawInterpolatedTri(RenderTools::Graphics& renderer, Geometry::Triangle const& tri) {
		Geometry::VertexData const* p0{ &tri.vertices[0] };
		Geometry::VertexData const* p1{ &tri.vertices[1] };
		Geometry::VertexData const* p2{ &tri.vertices[2] };

		std::swap(p0, min(min(p0, p1), p2)); std::swap(p1, min(p1, p2));

		/*Coord interpolation*/
		std::vector<int> p01{ Math::interpolateInt(static_cast<int>(p0->coord.y), p0->coord.x, static_cast<int>(p1->coord.y), p1->coord.x) };
		std::vector<int> p12{ Math::interpolateInt(static_cast<int>(p1->coord.y), p1->coord.x, static_cast<int>(p2->coord.y), p2->coord.x) };
		std::vector<int> p02{ Math::interpolateInt(static_cast<int>(p0->coord.y), p0->coord.x, static_cast<int>(p2->coord.y), p2->coord.x) };

		/*Color interpolation*/
		std::vector<Utils::Color> c01{ Math::interpolateColor(static_cast<int>(p0->coord.y), p0->color, static_cast<int>(p1->coord.y), p1->color) };
		std::vector<Utils::Color> c12{ Math::interpolateColor(static_cast<int>(p1->coord.y), p1->color, static_cast<int>(p2->coord.y), p2->color) };
		std::vector<Utils::Color> c02{ Math::interpolateColor(static_cast<int>(p0->coord.y), p0->color, static_cast<int>(p2->coord.y), p2->color) };

		/*Z interpolation*/
		std::vector<float> z01{ Math::interpolateFloat(static_cast<int>(p0->coord.y), p0->zBeforeProj, static_cast<int>(p1->coord.y), p1->zBeforeProj) };
		std::vector<float> z12{ Math::interpolateFloat(static_cast<int>(p1->coord.y), p1->zBeforeProj, static_cast<int>(p2->coord.y), p2->zBeforeProj) };
		std::vector<float> z02{ Math::interpolateFloat(static_cast<int>(p0->coord.y), p0->zBeforeProj, static_cast<int>(p2->coord.y), p2->zBeforeProj) };

		concat(p01, p12);
		concat(c01, c12);
		concat(z01, z12);

		int midpoint{ static_cast<int>(std::floorf(p01.size() / 2.f)) };

		std::vector<int> leftP;
		std::vector<int> rightP;

		std::vector<Utils::Color> leftC;
		std::vector<Utils::Color> rightC;

		std::vector<float> leftZ;
		std::vector<float> rightZ;

		if (p01[midpoint] > p02[midpoint]) {
			leftP = p02;
			leftC = c02;

			rightP = p01;
			rightC = c01;

			leftZ = z02;
			rightZ = z01;
		}
		else {
			leftP = p01;
			leftC = c01;

			rightP = p02;
			rightC = c02;

			leftZ = z01;
			rightZ = z02;
		}

		int endY{ static_cast<int>(p2->coord.y) };
		for (int y{ static_cast<int>(p0->coord.y) }; y <= endY; ++y) {

			int currY{ y - static_cast<int>(p0->coord.y) };

			int endX{ rightP[currY] };
			int startX{ leftP[currY] };

			std::vector<Utils::Color> interpolatedColVals{ Math::interpolateColor(startX, leftC[currY], endX, rightC[currY]) };
			std::vector<float> interpolatedZ{ Math::interpolateFloat(startX, leftZ[currY], endX, rightZ[currY])};

			for (int x{startX}; x <= endX; ++x) {
				renderer.putPixel(x, y, interpolatedColVals[x - startX].colorVal, interpolatedZ[x - startX]);
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
		std::vector<float> h01{ Math::interpolateFloat(static_cast<int>(p0->coord.y), p0->h, static_cast<int>(p1->coord.y), p1->h) };


		std::vector<int> x12{ Math::interpolateInt(static_cast<int>(p1->coord.y), p1->coord.x, static_cast<int>(p2->coord.y), p2->coord.x) };
		std::vector<float> h12{ Math::interpolateFloat(static_cast<int>(p1->coord.y), p1->h, static_cast<int>(p2->coord.y), p2->h) };

		std::vector<int> x02{ Math::interpolateInt(static_cast<int>(p0->coord.y), p0->coord.x, static_cast<int>(p2->coord.y), p2->coord.x) };
		std::vector<float> h02{ Math::interpolateFloat(static_cast<int>(p0->coord.y), p0->h, static_cast<int>(p2->coord.y), p2->h) };


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
				Math::interpolateFloat(static_cast<int>(xStart), h_left[y-yStart], static_cast<int>(xEnd), h_right[y-yStart]) 
			};

			for (int x{ xStart }; x < xEnd; ++x) {
				renderer.putPixel(x, y, color * hInterpolated[x - xStart]);
			}
		}

	}


}
