#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Vector3D.hpp"
#include "Matrix.hpp"
#include "Color.hpp"
#include <array>
#include <vector>


namespace Geometry {

	struct VertexData {
		Linear::Vector3D coord;
		Utils::Color color;
		float h;
		float zBeforeProj;
		//VertexData() = default;
		VertexData(Linear::Vector3D const& coord = Linear::Vector3D{}, 
			float const &h = 1.f, 
			Utils::Color const &color = Utils::Color{ 0 },
			float z = 0.f
		) : coord{ coord }, h{ h }, color{ color }, zBeforeProj{z} {}
	};

	using Vertices = std::array<VertexData, 3>;

	/*MUTATES VERTICES*/
	void transformVertices(Linear::Matrix4x4 & transformation, Vertices& vertices);

	struct Triangle {
		Vertices vertices;
		Linear::Vector3D normal;

		Triangle(VertexData const& p0 = VertexData{}, VertexData const& p1 = VertexData{}, VertexData const& p2 = VertexData{}, Linear::Vector3D const& normal = Linear::Vector3D{}) : normal{ normal } {
			vertices[0] = p0;
			vertices[1] = p1;
			vertices[2] = p2;
		}
	};

	using TriangleContainer = std::vector<Triangle>;

}


#endif