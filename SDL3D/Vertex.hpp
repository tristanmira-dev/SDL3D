#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Vector3D.hpp"
#include <array>

namespace Geometry {

	struct VertexData {
		Linear::Vector3D coord;
		VertexData() = default;
		VertexData(Linear::Vector3D const& coord) : coord{ coord } {}
	};

	struct Triangle {
		std::array<VertexData, 3> vertices;
		Linear::Vector3D normal;

		Triangle(VertexData const& p0, VertexData const& p1, VertexData const& p2, Linear::Vector3D const& normal) : normal{ normal } {
			vertices[0] = p0;
			vertices[1] = p1;
			vertices[2] = p2;
		}
	};


}


#endif