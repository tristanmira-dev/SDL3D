#include "Vertex.hpp"
#include "Matrix.hpp"

void Geometry::transformVertices(Linear::Matrix4x4& transformation, Vertices& vertices) {
	vertices[0].coord = transformation * vertices[0].coord;
	vertices[1].coord = transformation * vertices[1].coord;
	vertices[2].coord = transformation * vertices[2].coord;
}
