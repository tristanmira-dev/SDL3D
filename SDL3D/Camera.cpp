#include "Camera.hpp"
#include "Vector3D.hpp"

namespace Entity {
	Camera::Camera(Linear::Vector3D const& pos, Rotation const& rotation) : GameObject(pos, Linear::Vector3D{ 1.f, 1.f, 1.f }, rotation) {

	}
}