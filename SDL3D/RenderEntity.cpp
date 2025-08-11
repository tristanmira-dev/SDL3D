#include "RenderEntity.hpp"
#include "GameObject.hpp"
#include "Model.hpp"
#include "Shapes.hpp"
#include "Graphics.hpp"
#include "Camera.hpp"
#include "Plane.hpp"

#include <iostream>

namespace Entity {
	void renderEntity(Camera& camera, Model& model, GameObject& obj, RenderTools::Graphics& renderer) {

		Linear::PlaneCollection planes;

		float distance{ 2.f };
		float fov{ 120.f };
		Linear::setPlanes(distance, fov, planes);



		/*OBJECT TO WORLD TRANSFORMATION*/
		Linear::Vector3D gameObjPos{ obj.getPosition() };

		Linear::Matrix4x4 translate{ Linear::Matrix4x4::translateMatrix(gameObjPos.x, -gameObjPos.y, gameObjPos.z) };

		Linear::Vector3D size{ obj.getSize() };
		Linear::Matrix4x4 scaleMtx{ Linear::Matrix4x4::scaleMatrix(size.x, size.y, size.z)};

		Entity::Rotation rotation{ obj.getRotation() };
		Linear::Matrix4x4 yawMtx{ Linear::Matrix4x4::rotationYaw(rotation.yaw)};
		Linear::Matrix4x4 pitchMtx{ Linear::Matrix4x4::rotationPitch(rotation.pitch) };
		Linear::Matrix4x4 rollMtx{ Linear::Matrix4x4::rotationRoll(rotation.roll) };

		Linear::Matrix4x4 worldTransform{ translate * pitchMtx * yawMtx * rollMtx * scaleMtx };

		/*WORLD TO CAMERA TRANSFORMATION*/
		Linear::Matrix4x4 camTrans{ Linear::Matrix4x4::translateMatrix(-camera.getPosition().x, camera.getPosition().y, -camera.getPosition().z) };

		Entity::Rotation cameraRot{ camera.getRotation() };
		Linear::Matrix4x4 cameraYawMtx{ Linear::Matrix4x4::rotationYaw(-cameraRot.yaw) };
		Linear::Matrix4x4 cameraPitchMtx{ Linear::Matrix4x4::rotationPitch(-cameraRot.pitch) };
		Linear::Matrix4x4 finalTrans{ cameraPitchMtx * cameraYawMtx * camTrans * worldTransform };

		/*SCREEN SPACE TRANSFORMATION*/
		/*TRANSLATE TO MIDDLE OF THE SCREEN (SCREEN SPACE)*/
		float width{ renderer.getWidth() / 2.f };
		float height{ renderer.getHeight() / 2.f };

		Linear::Vector3D screenSpaceTrans{ width, height, 0.f };

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

			Geometry::transformVertices(finalTrans, newVertices);

			std::cout << Linear::signedDistance(planes.coll[Linear::CommonPlanesNormal::MIDDLE].normal, newVertices[0].coord) << '\n';


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

			projectedTri.vertices[0].coord += screenSpaceTrans;
			projectedTri.vertices[1].coord += screenSpaceTrans;
			projectedTri.vertices[2].coord += screenSpaceTrans;

			RenderTools::drawTriangle(renderer, projectedTri, 0xFF0000FF);
		}

	}
}