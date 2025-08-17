#include "Model.hpp"
#include "Shapes.hpp"
#include "Color.hpp"
#include "Matrix.hpp"

#include <cstdlib>

namespace Entity {
	Model::Model(std::initializer_list<Geometry::VertexData> listOfVertex) {

		for (Geometry::VertexData const& currentVertex : listOfVertex) {
			vertexContainer.push_back(currentVertex);
		}

	}
	void Model::insertTriangle(int idx1, int idx2, int idx3) {
		triContainer.push_back(Geometry::Triangle{
				
				vertexContainer[idx1],
				vertexContainer[idx2],
				vertexContainer[idx3],
				Linear::Vector3D {}
		});
	
	}
	void Model::renderGameObj(RenderTools::Graphics& renderer) {

		/*Linear::Matrix4x4 translate{ Linear::Matrix4x4::translateMatrix(0.0f, 0.0f, 3.f) };

		for (Geometry::Triangle& triangle : triContainer) {

			Geometry::Vertices newVertices{
				Geometry::VertexData {
					triangle.vertices[0].coord
				},
				Geometry::VertexData {
					triangle.vertices[1].coord
				},
				Geometry::VertexData {
					triangle.vertices[2].coord
				}
			};

			Geometry::transformVertices(translate, newVertices);


			Geometry::Triangle projectedTri{
				Geometry::VertexData {
					newVertices[0].coord.project(renderer)
				},
				Geometry::VertexData {
					newVertices[1].coord.project(renderer)
				},
				Geometry::VertexData {
					newVertices[2].coord.project(renderer)
				}
			};


			RenderTools::drawWireFrameTriangle(renderer, projectedTri, 0xFF0000FF);
		}*/

	}
	Geometry::TriangleContainer& Model::getTriContainer() {
		return triContainer;
	}
}