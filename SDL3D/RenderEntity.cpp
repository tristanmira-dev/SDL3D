#include "RenderEntity.hpp"
#include "GameObject.hpp"
#include "Model.hpp"
#include "Shapes.hpp"
#include "Graphics.hpp"

namespace Entity {
	void renderEntity(Model& model, GameObject& obj, RenderTools::Graphics &renderer) {

		Linear::Vector3D gameObjPos{ obj.getPosition()};

		Linear::Matrix4x4 translate{ Linear::Matrix4x4::translateMatrix(gameObjPos.x, gameObjPos.y, gameObjPos.z) };

		for (Geometry::Triangle& triangle : model.getTriContainer()) {

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
		}

	}
}