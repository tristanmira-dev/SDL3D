#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "Vector2D.hpp"
#include "Vector3D.hpp"
#include "Graphics.hpp"
#include "Vertex.hpp"
#include "Color.hpp"

namespace RenderTools {
	void drawLine(RenderTools::Graphics &renderer, Linear::Vector2D const &p0, Linear::Vector2D const &p1, Uint32 const& color);
	void drawWireFrameTriangle(RenderTools::Graphics& renderer, Geometry::Triangle const& triangle, Uint32 const& color);


	void drawTriangle(RenderTools::Graphics& renderer, Geometry::Triangle const &tri, Utils::Color const& color);
	void drawShadedTriangle(RenderTools::Graphics& renderer, Geometry::Triangle const& tri, Utils::Color const& color);
}



#endif