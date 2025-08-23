#include "GameObject.hpp"


namespace Entity {
	Linear::Vector3D GameObject::getPosition() {
		return position;
	}
	Linear::Vector3D GameObject::getSize() {
		return Linear::Vector3D{ this->size.x, this->size.y, this->size.z };
	}
	void GameObject::setX(float x) {
		this->position.x = x;
	}
	void GameObject::setY(float y) {
		this->position.y = y;
	}
	void GameObject::setZ(float z) {
		this->position.z = z;
	}
	Rotation GameObject::getRotation() {
		return rotation;
	}
	GameObject::GameObject(Linear::Vector3D const& pos, Linear::Vector3D const& size, Rotation const& rotation) 
		: position{ pos }, size{ size }, rotation{ rotation } 
	{
	
	}
}

