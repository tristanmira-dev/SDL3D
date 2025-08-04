#include "RenderEntity.hpp"
#include "GameObject.hpp"
#include "Model.hpp"
#include "Shapes.hpp"
#include "Graphics.hpp"
#include "Camera.hpp"

namespace Entity {
	void renderEntity(Camera &camera, Model& model, GameObject& obj, RenderTools::Graphics &renderer) {


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