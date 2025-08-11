#include "Vector3D.hpp"
#include "Graphics.hpp"
#include "Math.hpp"
#include <cmath>

namespace Linear {
	Vector3D::Vector3D(float x, float y, float z) : Vector2D(x, y), z{ z } {}
	Vector3D& Vector3D::operator+=(Vector3D const& src) {
		this->x += src.x;
		this->y += src.y;
		this->z += src.z;

		return (*this);
	}
	Vector3D Vector3D::operator+(Vector3D const& src) {
		return Vector3D{ this->x + src.x, this->y + src.y, this->z + src.z };
	}
	Vector3D Vector3D::operator-(Vector3D const& vec) const {
		return Vector3D{ this->x - vec.x, this->y - vec.y, this->z - vec.z };
	}
	bool Vector3D::operator==(Vector3D const& compare2) {
		return this->x == compare2.x && this->y == compare2.y && this->z == compare2.z;
	}
	Vector3D operator*(float const& val, Vector3D const& vec) {
		return Vector3D{val * vec.x, val * vec.y, val * vec.z};
	}
	Vector3D operator/(Vector3D const& vec, float const& val) {
		return Vector3D{ vec.x / val, vec.y / val, vec.z / val };
	}

	Vector3D Vector3D::project(RenderTools::Graphics const& renderer) {
		float pX{x/z};
		float pY{y/z};

		float viewport{ 2 * tanf(Math::toRad(60.f)) };

		float cX{ (pX/viewport) * renderer.getWidth()  };
		float cY{ (pY/viewport) * renderer.getHeight() };



		return Vector3D{cX, cY, 1.f};

	}


	

	float Vector3D::dot(Vector3D const& vec2) {
		return this->x * vec2.x + this->y * vec2.y + this->z * vec2.z;
	}

	float Vector3D::dot(Vector3D const& vec2) const {
		return this->x * vec2.x + this->y * vec2.y + this->z * vec2.z;
	}

	Vector3D Vector3D::normalize() {

		float length{ std::sqrtf(this->dot(*this)) };
		return Vector3D{ this->x / length, this->y / length, this->z / length };
	}

	Vector3D Vector3D::normalize() const {
		float length{ std::sqrtf(this->dot(*this)) };
		return Vector3D{ this->x / length, this->y / length, this->z / length };
	}
	


}