#include "Shapes.hpp"
#include "Graphics.hpp"
#include "Vector2D.hpp"
#include "Math.hpp"

#include <vector>
#include <cstdlib>

namespace RenderTools {
	void drawLine(RenderTools::Graphics& renderer, Linear::Vector2D const& p0, Linear::Vector2D const& p1, Uint32 const &color) {
		
		if (std::abs(p0.x - p1.x) >= std::abs(p0.y - p1.y)) {
			std::vector<int> values{ Math::interpolate(p0.x, p0.y, p1.x, p1.y) };

			int iVal{ static_cast<int>(p0.x) };

			for (int const& val : values) {
				renderer.putPixel(iVal, val, color);
				++iVal;
			}
		}
		else {
			std::vector<int> values{ Math::interpolate(p0.y, p0.x, p1.y, p1.x) };

			int iVal{ static_cast<int>(p0.y) };

			for (int const& val : values) {
				renderer.putPixel(iVal, val, color);
				++iVal;
			}
		}
		
		


	}
}
