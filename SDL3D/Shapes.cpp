#include "Shapes.hpp"
#include "Graphics.hpp"
#include "Vector2D.hpp"
#include "Math.hpp"

#include <vector>
#include <cstdlib>
#include <algorithm>

namespace RenderTools {
	void drawLine(RenderTools::Graphics& renderer, Linear::Vector2D const& p0, Linear::Vector2D const& p1, Uint32 const &color) {
		
		Linear::Vector2D const* newP0{ &p0 };
		Linear::Vector2D const* newP1{ &p1 };



		if (std::abs(p0.x - p1.x) >= std::abs(p0.y - p1.y)) {

			if (newP0->x > newP1->x) std::swap(newP0, newP1);
				
			std::vector<int> values{ Math::interpolate(newP0->x, newP0->y, newP1->x, newP1->y) };

			for (int x{ static_cast<int>(newP0->x) }; x <= newP1->x; ++x) {
				renderer.putPixel(x, values[x - newP0->x], color);
			}
		}
		else {

			if (newP0->y > newP1->y) std::swap(newP0, newP1);

			std::vector<int> values{ Math::interpolate(newP0->y, newP0->x, newP1->y, newP1->x) };

			for (int y{ static_cast<int>(newP0->y) }; y <= newP1->y; ++y) {
				renderer.putPixel(values[y - newP0->y], y, color);
			}
		}
		
		


	}
}
