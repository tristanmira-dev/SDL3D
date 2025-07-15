#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "Vector2D.hpp"
#include "Graphics.hpp"

namespace RenderTools {
	void drawLine(RenderTools::Graphics &renderer, Linear::Vector2D const &p0, Linear::Vector2D const &p1, Uint32 const& color);
	void drawWireFrameTriangle(RenderTools::Graphics& renderer, Linear::Vector2D const& p0, Linear::Vector2D const& p1,
		Linear::Vector2D const& p2, Uint32 const& color);

}



#endif