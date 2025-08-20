#include "RenderEntity.hpp"
#include "GameObject.hpp"
#include "Model.hpp"
#include "Shapes.hpp"
#include "Graphics.hpp"
#include "Camera.hpp"
#include "Plane.hpp"

#include <iostream>
#include <list>
#include <array>

namespace Entity {
	void renderEntity(Camera& camera, Model& model, GameObject& obj, RenderTools::Graphics& renderer) {

		Linear::PlaneCollection planes;

		float distance{ 1.f };
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
		float width{ (renderer.getWidth()) / 2.f };
		float height{ (renderer.getHeight()) / 2.f };
		Linear::Vector3D screenSpaceTrans{ width, height, 0.f };

		for (Geometry::Triangle& triangle : model.getTriContainer()) {
			

			Geometry::Triangle newTri{
				Geometry::VertexData {
					triangle.vertices[0]
				},
				Geometry::VertexData {
					triangle.vertices[1]
				},
				Geometry::VertexData {
					triangle.vertices[2]
				}
			};

			Geometry::transformVertices(finalTrans, newTri.vertices);

			/*BACKFACE CULLING*/
			Linear::Vector3D normalVec{
				(newTri.vertices[1].coord - newTri.vertices[0].coord).cross(newTri.vertices[2].coord - newTri.vertices[0].coord)
			};
			float test{ newTri.vertices[0].coord.dot(normalVec) };
			if (newTri.vertices[0].coord.dot(normalVec) >= 0.f) {
				continue;
			}
			/*---------------*/

			std::list<Geometry::Triangle> listTris{newTri};
			int newTriCount{ 1 };
			std::array<Geometry::Triangle, 2> clippedTris{};

			/*CLIP VERTICES*/
			int maxPlaneCount{ static_cast<int>(Linear::CommonPlanesNormal::MIDDLE) };
			for (int i{ static_cast<int>(Linear::CommonPlanesNormal::TOP) }; i <= maxPlaneCount; ++i) {
				
				int triAdded{};

				while (newTriCount > 0) {
					


					Geometry::Triangle head{ listTris.front() };
					listTris.pop_front();
					triAdded = Linear::clipTri(planes.coll[static_cast<Linear::CommonPlanesNormal>(i)], head, clippedTris[0], clippedTris[1]);
					for (int x{ 0 }; x < triAdded; ++x) {
						listTris.push_back(clippedTris[x]);
					}

					
					newTriCount--;
				}

				newTriCount = static_cast<int>(listTris.size());
			}

			
			for (Geometry::Triangle& triToRender : listTris) {
				Geometry::Triangle projected{ Geometry::VertexData{triToRender.vertices[0].coord.project(renderer, distance, fov), 1.f,triToRender.vertices[0].color, 1/triToRender.vertices[0].coord.z  } ,
					Geometry::VertexData{triToRender.vertices[1].coord.project(renderer, distance, fov), 1.f, triToRender.vertices[1].color, 1/triToRender.vertices[1].coord.z } ,
					Geometry::VertexData{triToRender.vertices[2].coord.project(renderer, distance, fov), 1.f, triToRender.vertices[2].color, 1/triToRender.vertices[2].coord.z }
				};
				


				projected.vertices[0].coord += screenSpaceTrans;
				projected.vertices[1].coord += screenSpaceTrans;
				projected.vertices[2].coord += screenSpaceTrans;

				RenderTools::drawInterpolatedTri(renderer, projected);

			}


		}

	}
}