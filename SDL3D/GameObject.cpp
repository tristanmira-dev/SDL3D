#include "GameObject.hpp"


namespace Entity {
	Linear::Vector3D GameObject::getPosition() {
		return position;
	}
	GameObject::GameObject(Linear::Vector3D const& pos) : position{ pos } {
	}
}

