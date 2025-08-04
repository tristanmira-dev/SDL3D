#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "Vector3D.hpp"

namespace Entity {
	struct Rotation {
		float yaw;
		float pitch;
		float roll;
	};

	class GameObject {
		public:
			Linear::Vector3D getPosition();
			Linear::Vector3D getSize();
			Rotation getRotation();
			GameObject(Linear::Vector3D const& pos, Linear::Vector3D const& size, Rotation const& rotation = Rotation{});
		protected:
			Linear::Vector3D position;
			Linear::Vector3D size;
			Rotation rotation;
	};
}



#endif
