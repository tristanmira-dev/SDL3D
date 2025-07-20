#include "Vector3D.hpp"
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
}