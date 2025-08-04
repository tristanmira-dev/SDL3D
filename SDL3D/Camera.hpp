#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.hpp"

namespace Entity {

	class Camera : public GameObject {
		public:
			Camera(Linear::Vector3D const& pos, Rotation const& rotation = Rotation{});


	};

}





#endif