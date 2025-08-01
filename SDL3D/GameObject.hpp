#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "Vector3D.hpp"

namespace Entity {
	class GameObject {
		public:
			Linear::Vector3D getPosition();
			GameObject(Linear::Vector3D const &pos);
		private:
			Linear::Vector3D position;

	};
}





#endif
